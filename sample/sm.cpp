#include <sitemap/sitemap.h>


sitemap g_site;

int main()
{
	// Site files
	g_site["home"] = { //file label
		"/index.html" //destination file
	};

	g_site["ddd"] = {"dfdf"};
	g_site["dddd"] = { sitemap::folder("dfdfd"), sitemap::folder("src") };

	// Content function, it must return std::vector<unsigned int>
	auto f = []() 
	{ 
		std::string s("<html>"); 
		s += "<body>";
		s += "<p>Hello World!</p>";
		s += "<a href='" + g_site["home"].dst() + "'>Home</a>";
		s += "</body>";

		std::vector<unsigned char> v; 
		std::copy(s.begin(), s.end(), std::back_inserter(v)); 
		return v;
	};
	
	// Content definition
	g_site["home"] = f;

	// Site root directory
	//
	g_site.set_root("./sample_site/");

	// Generate it
	g_site.generate("");
	return 0;
}
