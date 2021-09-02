#include <array>
#include <iostream>
#include <type_traits>

template<typename ... Args>
auto build_array(Args&&... args) -> std::array<typename std::common_type
<Args...>::type, sizeof...(args)>
{
	using commonType = typename std::common_type<Args...>::type;
	return {std::forward<commonType>((Args&&)args)...}; // 배열 생성
}

int main()
{
	auto data = build_array(1, 0u, 'a', 3.2f, false);

	for (auto i: data)
		std::cout << i << " ";
	std::cout << std::endl;

	// // data2 will make ERROR
	// // 문자열과 숫자를 모두 아우르는 공통타입(자료형)이 없기 때문에
	// // std::array보다 더 유연하고 향상된 기능이 필요하면 std::vector 사용을 추천
	// auto data2 = build_vector(1, "Packt", 2.0);
	// for (auto i: data)
	// 	std::cout << i << " ";
	// std::cout << std::endl;
}
