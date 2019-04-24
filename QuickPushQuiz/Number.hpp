#ifndef __NUMBER_HPP__
#define __NUMBER_HPP__
#include <string>
#include <type_traits>
#include <limits>
#include <algorithm>
#include <cassert>
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

namespace standard {
	namespace impl {
#if _HAS_CXX17 == 0
		template<typename T, class Compare> constexpr const T& clamp(const T& v, const T& lo, const T& hi, Compare comp) {
			return  assert(!comp(hi, lo)),
				comp(v, lo) ? lo : comp(hi, v) ? hi : v;
		}
#endif
		template<class T> constexpr const T& clamp(const T& v, const T& lo, const T& hi) {
#if _HAS_CXX17 == 0
			return clamp(v, lo, hi, std::less<>());
#else
			return std::clamp(v, lo, hi);
#endif
		}
	}
	template<typename T = int, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	class number {
	private:
		T n, maximum, minimum;
	protected:
		constexpr const T& cmp(const T num) {
			return impl::clamp(num, this->minimum, this->maximum);
		}
	public:
		number() = default;
		template<typename DefaultVal = T, typename MaxVal = T, typename MinVal = T,
			std::enable_if_t<std::is_arithmetic<DefaultVal>::value && std::is_arithmetic<MaxVal>::value && std::is_arithmetic<MinVal>::value, std::nullptr_t> = nullptr>
		constexpr number(const DefaultVal& num, const MaxVal max, const MinVal min) 
			: n(impl::clamp(static_cast<T>(num), static_cast<T>(min), static_cast<T>(max))), maximum(static_cast<T>(max)), minimum(static_cast<T>(min)) {}
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number(const U num) : number(static_cast<T>(num), std::numeric_limits<T>::max(), std::numeric_limits<T>::min()) {}
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number& operator = (const number<U>& num) { return standard::number<T>(num.n, num.maximum, num.minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number& operator = (number<U>&& num) { return standard::number<T>(std::move(num.n), std::move(num.maximum), std::move(minimum)); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator + (const number<U>& num) const { return number(this->n + num.Get<T>(), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator - (const number<U>& num) const { return number(this->n - num.Get<T>(), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator * (const number<U>& num) const { return number(this->n * num.Get<T>(), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator / (const number<U>& num) const {
			return num.Get<T>() != 0
				? number(this->n / num.Get<T>(), this->maximum, this->minimum) 
				: throw std::runtime_error("Divide value is 0");
		}
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator & (const number<U>& num) const { return number(this->n & num.Get<T>(), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator % (const number<U>& num) const {
			return num.Get<T>() != 0
				? number(this->n % num.Get<T>(), this->maximum, this->minimum)
				: throw std::runtime_error("Divide value is 0"); 
		}
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator | (const number<U>& num) const { return number(this->n | num.Get<T>(), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator ^ (const number<U>& num) const { return number(this->n ^ num.Get<T>(), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator << (const number<U>& num) const { return number(this->n << num.Get<T>(), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator >> (const number<U>& num) const { return number(this->n >> num.Get<T>(), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator += (const number<U>& num) { this->n = this->cmp(this->n + num.Get<T>()); return *this; }
		number& operator ++ () { this->n = this->cmp(this->n + 1); return *this; }
		number operator ++ (int) {
			const auto t = *this;
			this->n = this->cmp(this->n + 1); 
			return t;
		}
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator -= (const number<U>& num) { this->n = this->cmp(this->n - num.Get<T>()); return *this; }
		number& operator -- () { this->n = this->cmp(this->n - 1); return *this; }
		number operator -- (int) { 
			const auto t = *this;
			this->n = this->cmp(this->n - 1);
			return t;
		}
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator *= (const number<U>& num) { this->n = this->cmp(this->n * num.Get<T>()); return *this; }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator /= (const number<U>& num) {
			if (num.Get<T>() == 0) throw std::runtime_error("Divide value is 0");
			this->n = this->cmp(this->n = num.Get<T>()); 
			return *this;
		}
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator &= (const number<U>& num) { this->n = this->cmp(this->n & num.Get<T>()); return *this; }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator %= (const number<U>& num) {
			if (num.Get<T>() == 0) throw std::runtime_error("Divide value is 0");
			this->n = this->cmp(this->n % num.Get<T>());
			return *this;
		}
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator |= (const number<U>& num) { this->n = this->cmp(this->n | num.Get<T>()); return *this; }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator <<= (const number<U>& num) { this->n = this->cmp(this->n << num.Get<T>()); return *this; }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator >>= (const number<U>& num) { this->n = this->cmp(this->n >> num.Get<T>()); return *this; }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator + (const U & num) const { return number(this->n + static_cast<T>(num), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator - (const U & num) const { return number(this->n - static_cast<T>(num), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator * (const U & num) const { return number(this->n * static_cast<T>(num), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator / (const U & num) const {
			return static_cast<T>(num) != 0
				? number(this->n / static_cast<T>(num), this->maximum, this->minimum)
				: throw std::runtime_error("Divide value is 0");
		}
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator & (const U & num) const { return number(this->n & static_cast<T>(num), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator % (const U & num) const {
			return static_cast<T>(num) != 0
				? number(this->n % static_cast<T>(num), this->maximum, this->minimum)
				: throw std::runtime_error("Divide value is 0");
		}
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator | (const U & num) const { return number(this->n | static_cast<T>(num), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator ^ (const U & num) const { return number(this->n ^ static_cast<T>(num), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator << (const U & num) const { return number(this->n << static_cast<T>(num), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr number operator >> (const U & num) const { return number(this->n >> static_cast<T>(num), this->maximum, this->minimum); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator += (const U & num) { this->n = this->cmp(this->n + static_cast<T>(num)); return *this; }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator -= (const U & num) { this->n = this->cmp(this->n - static_cast<U>(num)); return *this; }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator *= (const U & num) { this->n = this->cmp(this->n * static_cast<T>(num)); return *this; }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator /= (const U & num) {
			if (static_cast<T>(num) == 0) throw std::runtime_error("Divide value is 0");
			this->n = this->cmp(this->n = static_cast<T>(num));
			return *this;
		}
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator &= (const U& num) { this->n = this->cmp(this->n & static_cast<T>(num)); return *this; }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator %= (const U& num) {
			if (static_cast<T>(num) == 0) throw std::runtime_error("Divide value is 0");
			this->n = this->cmp(this->n % static_cast<T>(num));
			return *this;
		}
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator |= (const U& num) { this->n = this->cmp(this->n | static_cast<T>(num)); return *this; }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator <<= (const U& num) { this->n = this->cmp(this->n << static_cast<T>(num)); return *this; }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		number operator >>= (const U& num) { this->n = this->cmp(this->n >> static_cast<T>(num)); return *this; }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr bool operator == (const number<U>& num) const { return this->n == num.Get<T>(); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr bool operator != (const number<U>& num) const { return this->n != num.Get<T>(); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr bool operator <  (const number<U>& num) const { return this->n < num.Get<T>(); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr bool operator <= (const number<U>& num) const { return this->n <= num.Get<T>(); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr bool operator >  (const number<U>& num) const { return this->n > num.Get<T>(); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr bool operator >= (const number<U>& num) const { return this->n >= num.Get<T>(); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr bool operator == (const U& num) const { return this->n == static_cast<T>(num); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr bool operator != (const U& num) const { return this->n != static_cast<T>(num); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr bool operator <  (const U& num) const { return this->n < static_cast<T>(num); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr bool operator <= (const U& num) const { return this->n <= static_cast<T>(num); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr bool operator >  (const U& num) const { return this->n > static_cast<T>(num); }
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr bool operator >= (const U& num) const { return this->n >= static_cast<T>(num); }
		template<typename U, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		operator number<U>() {
			return number<U>(
				this->n,
				this->maximum >= std::numeric_limits<U>::max() ? std::numeric_limits<U>::max() : this->maximum,
				this->minimum <= std::numeric_limits<U>::min() ? std::numeric_limits<U>::min() : this->minimum
				);
		}
		// 現在値を取得する
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr U Get() const noexcept { return static_cast<U>(this->n); }
		// 設定されている現在の最大値を取得する
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr U GetMax() const noexcept { return static_cast<U>(this->maximum); }
		// 設定されている現在の最大値を取得する
		template<typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
		constexpr U GetMin() const noexcept { return static_cast<U>(this->minimum); }
		// 現在値を指定された値に変更する
		void ChangeCurrentNumToReserevedNum(const T num) { this->n = static_cast<T>(num); }
		// 最大値を指定された値に変更する
		// 例外 : 引数に指定された値が現在の最小値より小さい場合、std::runtime_errorが投げられる
		void ChangeMaximumToReservedNum(const T num) {
			if (num < this->minimum) throw std::runtime_error("maximum must be larger than minimum.");
			this->maximum = static_cast<T>(num);
			this->n = this->cmp(this->n);
		}
		// 最小値を指定された値に変更する
		// 例外 : 引数に指定された値が現在の最大値より大きい場合、std::runtime_errorが投げられる
		void ChangeMinimumToReservedNum(const T num) {
			if (num > this->maximum) throw std::runtime_error("minimum must be smaller than maximum.");
			this->minimum = static_cast<T>(num);
			this->n = this->cmp(this->n);
		}
		// 最大値に指定された値を加算する
		// 例外 : 引数に指定された値が負の場合、計算することによって最大値が最小値を下回る場合、std::runtime_errorが投げられる
		void AddToMax(const T num) { this->ChangeMaximumToReservedNum(this->GetMax() + num); }
		// 最大値に指定された値を加算する
		// 例外 : 引数に指定された値が正の場合、計算することによって最小値が最大値を上回る場合、std::runtime_errorが投げられる
		void AddToMin(const T num) { this->ChangeMinimumToReservedNum(this->GetMin() + num); }
	};
	template<typename T, typename U = T, typename V = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	constexpr const number<T>& clamp(const number<T>& v, const number<U>& lo, const number<V>& hi) { return number<T>(clamp<T>(v.Get(), lo.Get<T>(), hi.Get<T>())); }
	template<typename T, typename U = T, typename V = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	constexpr const number<T>& clamp(const T& v, const number<U>& lo, const number<V>& hi) { return number<T>(clamp<T>(v, lo.Get<T>(), hi.Get<T>())); }
	template<typename T, typename U = T, typename V = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	constexpr const number<T>& clamp(const number<T>& v, const U& lo, const number<V>& hi) { return number<T>(clamp<T>(v.Get(), static_cast<T>(lo), hi.Get<T>())); }
	template<typename T, typename U = T, typename V = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	constexpr const number<T>& clamp(const number<T>& v, const number<U>& lo, const V& hi) { return number<T>(clamp<T>(v.Get(), lo.Get<T>(), static_cast<T>(hi))); }
	template<typename T, typename U = T, typename V = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	constexpr const number<T>& clamp(const T& v, const U& lo, const number<V>& hi) { return number<T>(clamp<T>(v, static_cast<T>(lo), hi.Get<T>())); }
	template<typename T, typename U = T, typename V = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	constexpr const number<T>& clamp(const T& v, const number<U>& lo, const V& hi) { return number<T>(clamp<T>(v, lo.Get(), static_cast<T>(hi))); }
	template<typename T, typename U = T, typename V = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	constexpr const number<T>& clamp(const number<T>& v, const U& lo, const V& hi) { return number<T>(clamp<T>(v.Get(), static_cast<T>(lo), static_cast<T>(hi))); }

	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline number<T> operator + (const T& n, const number<U>& num) { return number<T>(impl::clamp(n + num.Get<T>(), num.GetMin(), num.GetMax()), num.GetMax(), num.GetMin()); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline number<T> operator - (const T& n, const number<U>& num) { return number<T>(impl::clamp(n - num.Get<T>(), num.GetMin(), num.GetMax()), num.GetMax(), num.GetMin()); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline number<T> operator * (const T& n, const number<U>& num) { return number<T>(impl::clamp(n * num.Get<T>(), num.GetMin(), num.GetMax()), num.GetMax(), num.GetMin()); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline number<T> operator / (const T& n, const number<U>& num) { return number<T>(impl::clamp(n / num.Get<T>(), num.GetMin(), num.GetMax()), num.GetMax(), num.GetMin()); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline number<T> operator & (const T& n, const number<U>& num) { return number<T>(impl::clamp(n & num.Get<T>(), num.GetMin(), num.GetMax()), num.GetMax(), num.GetMin()); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline number<T> operator % (const T& n, const number<U>& num) { return number<T>(impl::clamp(n % num.Get<T>(), num.GetMin(), num.GetMax()), num.GetMax(), num.GetMin()); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline number<T> operator | (const T& n, const number<U>& num) { return number<T>(impl::clamp(n | num.Get<T>(), num.GetMin(), num.GetMax()), num.GetMax(), num.GetMin()); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline number<T> operator ^ (const T& n, const number<U>& num) { return number<T>(impl::clamp(n ^ num.Get<T>(), num.GetMin(), num.GetMax()), num.GetMax(), num.GetMin()); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline number<T> operator << (const T& n, const number<U>& num) { return number<T>(impl::clamp(n << num.Get<T>(), num.GetMin(), num.GetMax()), num.GetMax(), num.GetMin()); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline number<T> operator >> (const T& n, const number<U>& num) { return number<T>(impl::clamp(n >> num.Get<T>(), num.GetMin(), num.GetMax()), num.GetMax(), num.GetMin()); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline bool operator == (const T& n, const number<U>& num) { return n == num.Get<T>(); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline bool operator != (const T& n, const number<U>& num) { return n != num.Get<T>(); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline bool operator <  (const T& n, const number<U>& num) { return n < num.Get<T>(); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline bool operator <= (const T& n, const number<U>& num) { return n <= num.Get<T>(); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline bool operator >  (const T& n, const number<U>& num) { return n > num.Get<T>(); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	inline bool operator >= (const T& n, const number<U>& num) { return n >= num.Get<T>(); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
	inline bool operator == (const T& a, const standard::number<U>& b) { return a == b.Get<T>(); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
	inline bool operator != (const T& a, const standard::number<U>& b) { return a != b.Get<T>(); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
	inline bool operator <  (const T& a, const standard::number<U>& b) { return a < b.Get<T>(); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
	inline bool operator <= (const T& a, const standard::number<U>& b) { return a <= b.Get<T>(); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
	inline bool operator >  (const T& a, const standard::number<U>& b) { return a > b.Get<T>(); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<U>::value, std::nullptr_t> = nullptr>
	inline bool operator >= (const T& a, const standard::number<U>& b) { return a >= b.Get<T>(); }

	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	constexpr const number<T>& max(const number<T>& Left, const number<U>& Right) { return number<T>(std::max(Left.Get(), Right.Get())); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	constexpr const number<T>& max(const number<T>& Left, const U& Right) { return number<T>(std::max(Left.Get(), Right)); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	constexpr const number<T>& max(const T& Left, const number<U>& Right) { return number<T>(std::max(Left, Right.Get())); }

	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	constexpr const number<T>& min(const number<T>& Left, const number<U>& Right) { return number<T>(std::min(Left.Get(), Right.Get())); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	constexpr const number<T>& min(const number<T>& Left, const U& Right) { return number<T>(std::min(Left.Get(), Right)); }
	template<typename T, typename U = T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
	constexpr const number<T>& min(const T& Left, const number<U>& Right) { return number<T>(std::min(Left, Right.Get())); }

	inline number<long double> abs(const number<long double> n) { return number<long double>(std::abs(n.Get())); }
	inline number<double> abs(const number<double> n) { return number<double>(std::abs(n.Get())); }
	inline number<float> abs(const number<float> n) { return number<float>(std::abs(n.Get())); }
	inline number<long long> abs(const number<long long> n) { return number<long long>(std::abs(n.Get())); }
	inline number<long> abs(const number<long> n) { return number<long>(std::abs(n.Get())); }
	inline number<int> abs(const number<int> n) { return number<int>(std::abs(n.Get())); }

	namespace {
		template<typename T, std::enable_if_t<std::is_signed<T>::value, std::nullptr_t> = nullptr>
		number<T> string_to_signed_integer(const std::string& s, size_t* Index = 0, const int Base = 10) { return number<T>(static_cast<T>(std::stoll(s, Index, Base))); }
		template<typename T, std::enable_if_t<std::is_signed<T>::value, std::nullptr_t> = nullptr>
		number<T> wstring_to_signed_integer(const std::wstring& s, size_t* Index = 0, const int Base = 10) { return number<T>(static_cast<T>(std::stoll(s, Index, Base))); }
		template<typename T, std::enable_if_t<std::is_unsigned<T>::value, std::nullptr_t> = nullptr>
		number<T> string_to_unsigned_integer(const std::string& s, size_t* Index = 0, const int Base = 10) { return number<T>(static_cast<T>(std::stoull(s, Index, Base))); }
		template<typename T, std::enable_if_t<std::is_unsigned<T>::value, std::nullptr_t> = nullptr>
		number<T> wstring_to_unsigned_integer(const std::wstring& s, size_t* Index = 0, const int Base = 10) { return number<T>(static_cast<T>(std::stoull(s, Index, Base))); }
		template<typename T, std::enable_if_t<std::is_floating_point<T>::value, std::nullptr_t> = nullptr>
		number<T> string_to_float(const std::string s, size_t* Index = 0) { return number<T>(static_cast<T>(std::stold(s, Index))); }
		template<typename T, std::enable_if_t<std::is_floating_point<T>::value, std::nullptr_t> = nullptr>
		number<T> wstring_to_float(const std::wstring s, size_t* Index = 0) { return number<T>(static_cast<T>(std::stold(s, Index))); }
	}
	inline number<int> stoi(const std::string& s, size_t* Index = 0, const int Base = 10) { return string_to_signed_integer<int>(s, Index, Base); }
	inline number<int> stoi(const std::wstring& s, size_t* Index = 0, const int Base = 10) { return wstring_to_signed_integer<int>(s, Index, Base); }
	inline number<long> stol(const std::string& s, size_t* Index = 0, const int Base = 10) { return string_to_signed_integer<long>(s, Index, Base); }
	inline number<long> stol(const std::wstring& s, size_t* Index = 0, const int Base = 10) { return wstring_to_signed_integer<long>(s, Index, Base); }
	inline number<__int64> stoll(const std::string& s, size_t* Index = 0, const int Base = 10) { return string_to_signed_integer<__int64>(s, Index, Base); }
	inline number<__int64> stoll(const std::wstring& s, size_t* Index = 0, const int Base = 10) { return wstring_to_signed_integer<__int64>(s, Index, Base); }
	inline number<unsigned int> stoui(const std::string& s, size_t* Index = 0, const int Base = 10) { return string_to_unsigned_integer<unsigned int>(s, Index, Base); }
	inline number<unsigned int> stoui(const std::wstring& s, size_t* Index = 0, const int Base = 10) { return wstring_to_unsigned_integer<unsigned int>(s, Index, Base); }
	inline number<unsigned long> stoul(const std::string& s, size_t* Index = 0, const int Base = 10) { return string_to_unsigned_integer<unsigned long>(s, Index, Base); }
	inline number<unsigned long> stoul(const std::wstring& s, size_t* Index = 0, const int Base = 10) { return wstring_to_unsigned_integer<unsigned long>(s, Index, Base); }
	inline number<unsigned __int64> stoull(const std::string& s, size_t* Index = 0, const int Base = 10) { return string_to_unsigned_integer<unsigned __int64>(s, Index, Base); }
	inline number<unsigned __int64> stoull(const std::wstring& s, size_t* Index = 0, const int Base = 10) { return wstring_to_unsigned_integer<unsigned __int64>(s, Index, Base); }
	inline number<float> stof(const std::string& s, size_t* Index = 0) { return string_to_float<float>(s, Index); }
	inline number<float> stof(const std::wstring& s, size_t* Index = 0) { return wstring_to_float<float>(s, Index); }
	inline number<double> stod(const std::string& s, size_t* Index = 0) { return string_to_float<double>(s, Index); }
	inline number<double> stod(const std::wstring& s, size_t* Index = 0) { return wstring_to_float<double>(s, Index); }
	inline number<long double> stold(const std::string& s, size_t* Index = 0) { return string_to_float<long double>(s, Index); }
	inline number<long double> stold(const std::wstring& s, size_t* Index = 0) { return wstring_to_float<long double>(s, Index); }
}
#endif
