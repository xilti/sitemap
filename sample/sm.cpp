#include <iterator>
#include <sitemap/sitemap.h>

int main()
{
	sitemap sm;

	sm["test"] = {"/test.txt", []() { std::string s("test\n\n"); std::vector<unsigned char> v; std::copy(s.begin(), s.end(), std::back_inserter(v)); return v;}};
	sm.set_root("./");
	sm.generate("");
	return 0;
}
