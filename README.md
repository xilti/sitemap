jj# sitemap
Sitemap is a file transfer library.

I originally built this tiny library for generating web sites. 
It allows you to define your web site layout and content sources. 
There is a few basic steps. First, you define locations of your 
site files and folders, and give them labels. The labels can be used later for referencing the site links later.
It lets you control the whole site layout in one place without modifying the reset of the code.


	sitemap["home"] =  {"/index.html"};
	sitemap["about"] = {"/about/index.html"};
	...
  
If some of the source content already exists, for example css files or the jquery library. You can specify them as such.

	sitemap["home_css"] = {"/css/home.css", "/sitecss/home.css"];
	sitemap["jquery"] = {sitemap::folder("/js/jquery"), sitemap::folder("/lib/jquery"];

The source folders and files like sitecss/home.css and /lib/jquery are written relative to some root source folder that you define later.


Next, you specify how the dynamic content is produced by setting functions that return std::vector<unsigned char>. It is better to show it with an example (see the sample folder).


	// Content function, it must return std::vector&lt;unsigned int$gt;
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


The set_root function sets the location of the site root directory.

	sitemap:set_root("/var/www/mysite");

The last step is to run it.

	sitemap::generate("/path/to/source/files/and/folders");

The input parameter is the root folder for the relative paths used earlier, sitecss/home.css and lib/jquery.

That's it!
