# sitemap
Sitemap is a file transfer library.

I originally built this tiny library for generating web sites. 
It is used to define a web site layout and its content sources. 
There is a few basic steps. First, you define locations of your 
site files and folders, and give them labels. The labels can be used later for referencing the site links, that
allows you to control the whole layout in one place without modifying the reset of the code.


	sitemap["home"] =  {"/index.html"};
	sitemap["about"] = {"/about/index.html"};
	...
  
If some of the source content already exists, for example css files or the jquery library. You can specify them as such.

	sitemap["home_css"] = {"/css/home.css", "/sitecss/home.css"];
	sitemap["jquery"] = {sitemap::folder("/js/jquery"), sitemap::folder("/lib/jquery"];

The source folders and files like sitecss/home.css and /lib/jquery are written relative to some root source folder that you define later.


The next step is to define your dynamic content. This is done with functions that return std::vector<unsigned char>. 
It is better to show it with an example. Also, see the sample folder.


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
	
	// link content function with the site 
	g_site["home"] = f;


The set_root function sets the location of the site root directory.

	sitemap:set_root("/var/www/mysite");

The last step is to run it.

	sitemap::generate("/path/to/source/files/and/folders");

The input parameter is the root folder of the relative paths for the source files and folders, sitecss/home.css and lib/jquery, etc..

That's it!

## Build

### Requirements
Boost, C++11 or later

### Steps
* Suppose you cloned to [HOME]/work/sitemap
* For out-of-source, create a build folder in [HOME]/work, and go there.

		$mkdir build
		$cd build

* Run cmake.

		$cmake ../sitemap

* Build it.     

		$make

* You should get the sitemap library, like libsitemap.a and a sample binary, 'sm'.

