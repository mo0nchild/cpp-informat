#define _USE_MATH_DEFINES

#include <cmath>
#include <functional>
#include <iostream>
#include <memory>

export module lab6_module;

namespace lab6 {
	export struct LabResult {
		using ResultList = std::vector<std::pair<double, double>>;

		LabResult(double x, double y) : x(x), y(y) { }
		LabResult(const LabResult& copy) = delete;
		~LabResult() { std::cout << "result was deleted" << std::endl; }

		LabResult::ResultList get_list() const { return this->result_list; }
		int get_i() const { return this->result_list.size(); }

		double get_x() const { return this->x; }
		double get_y() const { return this->y; }

		LabResult* connect_list(LabResult::ResultList list) {
			this->result_list = list; return this;
		}
	private:
		double x = double(0), y = double(0);
		LabResult::ResultList result_list{};
	};

	export class LabCalculator {
		std::function<const double(double, double)> _func;
		double (*_g)(double); double (*_v)(double); double (*_w)(double);

		const double ESP = std::pow(10, -3);
		bool is_automatic = false;
	public:
		LabCalculator(double (*g)(double), double (*v)(double), double (*w)(double)) : _g(g), _v(v), _w(w) {
			this->_func = [&](double x, double y) { return _v(x) * _w(x) - _g(x) * y; };
		}

		lab6::LabCalculator* set_automatic() noexcept { this->is_automatic = true; return this; }
		lab6::LabCalculator* off_automatic() noexcept { this->is_automatic = false; return this; }

		LabCalculator(const LabCalculator& copy) = delete;
		~LabCalculator() = default;

		inline std::shared_ptr<lab6::LabResult> calculate_value(double h, double x0, double x_k, double y0) const;
	};

	std::shared_ptr<lab6::LabResult> LabCalculator::calculate_value(double h0, double x0, double x_k, double y0) const {
		double x_i = x0, y_i = y0, h = h0;
		LabResult::ResultList list{};

		if (this->is_automatic) {
			for (; true;) {
				double y_v = this->_func(x0 + h, y0);
				double y_v2 = this->_func(x0 + h / 2, y0);

				double sigma = fabs(y_v - y_v2) / fabs(pow(2, 4) + 1);
				if (sigma >= this->ESP) h /= 2;
				else break;
			}
		}

		for (int i = 0; x_i < x_k; i++) {
			if (this->is_automatic) {
				while (true) {
					double y_v = this->_func(x0 + h, y0);
					double y_v2 = this->_func(x0 + h / 2, y0);

					double sigma = fabs(y_v - y_v2) / fabs(pow(2, 4) + 1);
					if (sigma < (this->ESP / pow(2, 5))) h *= 2;
					else break;
				}
			}

			double k1 = h * this->_func(x_i, y_i),
				k2 = h * this->_func(x_i + h / 2, y_i + k1 / 2),
				k3 = h * this->_func(x_i + h / 2, y_i + k2 / 2),
				k4 = h * this->_func(x_i + h, y_i + k3);

			y_i += (1. / 6 * (k1 + 2 * k2 + 2 * k3 + k4));
			x_i += h;
			list.push_back(std::pair<double, double>(x_i, y_i));
		}
		return std::shared_ptr<lab6::LabResult>((new LabResult(x_i, y_i))->connect_list(list));
	}

	export void run_calculator() noexcept {

		lab6::LabCalculator* calculator = new lab6::LabCalculator(
			[](double x) -> double { return -sin(x + 1); },
			[](double x) -> double { return pow(M_E, -(x + 4) * 2); },
			[](double x) -> double { return 0.01; }
		);
		const std::shared_ptr<lab6::LabResult> result1 = calculator->set_automatic()
			->calculate_value(0.5, -1, 2 * M_PI - 1, 8);

		const double h = (double)((2 * M_PI - 1) - (-1)) / result1.get()->get_i();
		const std::shared_ptr<lab6::LabResult> result2 = calculator->off_automatic()
			->calculate_value(h, -1, 2 * M_PI - 1, 8);

		delete calculator;

		std::printf("|%5s|%7s|%7s|%7s|%7s|\n", "i", "x1", "y1", "x2", "y2");
		for (int i = 0; i < result1.get()->get_i(); i++) {
			auto current_result1 = result1.get()->get_list()[i];
			auto current_result2 = result2.get()->get_list()[i];

			std::printf("|%5d|%7.3lf|%7.3lf|%7.3lf|%7.3lf|\n", i, current_result1.first, current_result1.second,
				current_result2.first, current_result2.second);
		}

		std::cout << "a) i: " << result1.get()->get_i() << "; x: " << result1.get()->get_x()
			<< "; y: " << result1.get()->get_y() << std::endl;

		std::cout << "á) i: " << result2.get()->get_i() << "; x: " << result2.get()->get_x()
			<< "; y: " << result2.get()->get_y() << std::endl;
	}
}