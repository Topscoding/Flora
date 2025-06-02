#pragma once
#include "../include/include.h"
#include "../include/define.h"
constexpr u64 bigint_digit_limit = 1ull << 32;
class bigint {
// private
	bool is_positive = true;
	vector<u32> digits;
	static u64 mod_2_32(const string &str) {
		u64 remainder = 0;
		for (const char c: str) {
			if (!isdigit(c)) {
				continue;
			}
			const u64 digit = c - '0';
			remainder = (remainder * 10 + digit) % bigint_digit_limit;
		}
		return remainder;
	}
	static string div_2_32(const string &str) {
		string result;
		u64 current = 0;
		bool leading_zero = true;
		for (const char c : str) {
			if (!isdigit(c)) {
				continue;
			}
			const u64 digit = c - '0';
			current = current * 10 + digit;
			if (current >= bigint_digit_limit) {
				u64 quotient = current / bigint_digit_limit;
				result += std::to_string(quotient);
				current = current % bigint_digit_limit;
				leading_zero = false;
			} else if (!leading_zero) {
				result += '0';
			}
		}
		if (result.empty()) {
			return "0";
		}
		return result;
	}
	static vector<u32> simple_add(const vector<u32> &a, const vector<u32> &b) {
		const usize max_size = max(a.size(), b.size());
		vector<u32> result;
		result.reserve(max_size + 1);
		u64 carry = 0;
		for (usize i = 0; i < max_size; i++) {
			u64 sum = carry;
			if (i < a.size())
				sum += a[i];
			if (i < b.size())
				sum += b[i];
			result.push_back(static_cast<u32>(sum % bigint_digit_limit));
			carry = sum / bigint_digit_limit;
		}
		if (carry > 0) {
			result.push_back(static_cast<u32>(carry));
		}
		return result;
	}
	static vector<u32> simple_sub(const vector<u32> &a, const vector<u32> &b) {
		vector<u32> result;
		result.reserve(a.size());
		i64 borrow = 0;
		for (usize i = 0; i < a.size(); i++) {
			const i64 digit_a = a[i];
			const i64 digit_b = (i < b.size()) ? b[i] : 0;
			i64 diff = digit_a - digit_b - borrow;
			if (diff < 0) {
				diff += bigint_digit_limit;
				borrow = 1;
			} else {
				borrow = 0;
			}
			result.push_back(static_cast<u32>(diff));
		}
		while (result.size() > 1 && result.back() == 0) {
			result.pop_back();
		}
		return result;
	}
	static vector <u32> basic_mul(const vector<u32> &a, const vector<u32> &b) {
		vector<u64> result(a.size() + b.size() - 1, 0);
		for (usize i = 0; i < a.size(); i ++) {
			for (usize j = 0; j < b.size(); j ++) {
				result[i + j] += static_cast<u64>(a[i]) * b[j];
				result[i + j + 1] += result[i + j] / bigint_digit_limit;
				result[i + j] %= bigint_digit_limit;
			}
		}
		while (result.size() > 1 && result.back() == 0) {
			result.pop_back();
		}
		vector<u32> ret(result.size(), 0);
		for (auto i : result) {
			ret.emplace_back(i);
		}
		return ret;
	}
	static vector <u32> shift_left(const vector<u32> &x, const u32 bits) {
		vector<u32> result(bits, 0);
		for (auto i : x) {
			result.push_back(i);
		}
		return result;
	}
	static vector<u32> karatsuba_mul(const vector<u32>& a, const vector<u32>& b) {
		if (a.size() < 16 || b.size() < 16) {
			return basic_mul(a, b);
		}
		const isize m = static_cast<isize>(min(a.size(), b.size())) / 2;
		const vector a_low(a.begin(), a.begin() + m);
		const vector a_high(a.begin() + m, a.end());
		const vector b_low(b.begin(), b.begin() + m);
		const vector b_high(b.begin() + m, b.end());
		const vector<u32> z0 = karatsuba_mul(a_low, b_low);
		const vector<u32> z2 = karatsuba_mul(a_high, b_high);
		const vector<u32> a_sum = simple_add(a_low, a_high);
		const vector<u32> b_sum = simple_add(b_low, b_high);
		vector<u32> z1 = karatsuba_mul(a_sum, b_sum);
		z1 = simple_sub(z1, z0);
		z1 = simple_sub(z1, z2);
		vector<u32> result = shift_left(z2, 2 * m);
		result = simple_add(result, shift_left(z1, m));
		result = simple_add(result, z0);
		while (result.size() > 1 && result.back() == 0) {
			result.pop_back();
		}
		return result;
	}
public:
	bool operator<(const bigint &other) const {
		if (is_positive ^ other.is_positive) { // !=
			return is_positive < other.is_positive;
		}
		if (digits.size() != other.digits.size()) {
			return is_positive ? digits.size() < other.digits.size() : digits.size() > other.digits.size();
		}
		for (auto i = static_cast <isize> (digits.size()) - 1; i >= 0; i --) {
			if (digits[i] != other.digits[i]) {
				return is_positive ? digits[i] < other.digits[i] : other.digits[i] < digits[i];
			}
		}
		return false; // ==
	}
	bool operator>(const bigint &other) const {
		if (is_positive ^ other.is_positive) {
			return is_positive > other.is_positive;
		}
		if (digits.size() != other.digits.size()) {
			return is_positive ? digits.size() > other.digits.size() : other.digits.size() > digits.size();
		}
		for (auto i = static_cast <isize> (digits.size()) - 1; i >= 0; i --) {
			if (digits[i] != other.digits[i]) {
				return is_positive ? digits[i] > other.digits[i] : other.digits[i] > digits[i];
			}
		}
		return false; // ==
	}
	[[nodiscard]] bool is_zero() const {
		if (digits.empty())
			return true;
		if (digits.size() == 1 && digits[0] == 0)
			return true;
		return false;
	}
	bool operator==(const bigint &other) const {
		if (is_zero() && other.is_zero())
			return true;
		return is_positive == other.is_positive && digits == other.digits;
	}
	bool operator!=(const bigint &other) const {
		return !(*this == other);
	}
	bool operator<=(const bigint &other) const {
		return !(*this > other);
	}
	bool operator>=(const bigint &other) const {
		return !(*this < other);
	}
	bigint operator+(const bigint &other) const {
		if (is_positive ^ other.is_positive) { // !=
			if (is_positive) {
				if (*this >= other.abs()) {
					bigint result;
					result.is_positive = true;
					result.digits = simple_sub(digits, other.digits);
					return result;
				}
				bigint result;
				result.is_positive = false;
				result.digits = simple_sub(other.digits, digits);
				return result;
			}
			if (this -> abs() >= other) {
				bigint result;
				result.is_positive = false;
				result.digits = simple_sub(digits, other.digits);
				return result;
			}
			bigint result;
			result.is_positive = true;
			result.digits = simple_sub(other.digits, digits);
			return result;
		}
		// both positive or both negatives
		bigint result;
		result.is_positive = is_positive;
		result.digits = simple_add(digits, other.digits);
		return result;
	}
	bigint operator-() const {
		bigint result = *this;
		result.is_positive = !is_positive;
		return result;
	}
	bigint operator-(const bigint &other) const {
		if (is_positive ^ other.is_positive) { // !=
			if (is_positive) {
				return *this + other.abs();
			}
			bigint result = this->abs() + other;
			result.is_positive = !result.is_positive;
			return result;
		}
		if (is_positive) {
			if (*this >= other) {
				bigint result;
				result.is_positive = true;
				result.digits = simple_sub(this -> digits, other.digits);
				return result;
			}
			bigint result;
			result.is_positive = false;
			result.digits = simple_sub(other.digits, this -> digits);
			return result;
		}
		return *this + other.abs();
	}
	bigint operator*(const bigint &other) const {
		if (is_zero() || other.is_zero()) {
			return {};
		}
		bigint result;
		result.is_positive = !(is_positive ^ other.is_positive);
		result.digits = digits.size() > 128 && other.digits.size() > 128 ?
		karatsuba_mul(digits, other.digits) : basic_mul(digits, other.digits);
		return result;
	}
	bigint &operator+=(const bigint &other) {
		*this = *this + other;
		return *this;
	}
	bigint &operator-=(const bigint &other) {
		*this = *this - other;
		return *this;
	}
	bigint &operator*=(const bigint &other) {
		*this = *this * other;
		return *this;
	}
	constexpr bigint() {digits = {0};}
	explicit bigint(string value) {
		if (value[0] == '-') {
			is_positive = false;
			value = value.substr(1);
		}
		while (value != "0" && !value.empty()) {
			digits.push_back(mod_2_32(value));
			value = div_2_32(value);
		}
	}
	[[nodiscard]] string to_string() const {
		if (digits.empty())
			return "0";
		vector<u32> num = digits;
		string result;
		while (!num.empty() && !(num.size() == 1 && num[0] == 0)) {
			u64 remainder = 0;
			for (auto i = static_cast<isize>(num.size()) - 1; i >= 0; i--) {
				const u64 value = remainder << 32 | num[i];
				num[i] = value / 10;
				remainder = value % 10;
			}
			result.push_back(static_cast<char>(remainder + '0'));
			while (num.size() > 1 && num.back() == 0) {
				num.pop_back();
			}
		}
		if (result.empty())
			result = "0";
		if (!is_positive)
			result.push_back('-');
		ranges::reverse(result);
		return result;
	}
	[[nodiscard]] constexpr bigint abs() const {
		bigint result = *this;
		result.is_positive = true;
		return result;
	}
};
