#include <fstream>
#include <algorithm>
#include <iterator>
#include <sitemap/sitemap.h>

namespace fs = boost::filesystem;

namespace
{
	void copy_dir( const fs::path& dst, const fs::path& src )
	{
		fs::create_directory(dst);

		// Iterate through the source directory
		for (fs::directory_iterator file(src); file != fs::directory_iterator(); ++file) {
			fs::path current(file->path());
			if (fs::is_directory(current)) {
				copy_dir(
						dst / current.filename()
						,current
						);
			}		
			else {
				try {
					fs::remove(dst / current.filename());
				}
				catch( const std::exception& )
				{}

				fs::copy_file( current, dst / current.filename());
			}
		}
	}
}

void sitemap::generate(const path& src_root)
{
	if (root_.empty()) {
		throw std::runtime_error("The root hasn't been set");
	}
	for (const auto& v: i_) {
		fs::path dst = (root_ / v.second.dst_ );
		if (v.second.t_ == item::t_content) {
			if (!v.second.cont_) {
				throw std::runtime_error(std::string("content function is empty: ") + v.first);
			}

			//create folder
			fs::create_directories(dst.branch_path());

			//create file
			std::ofstream file(dst.string().c_str(), std::ios::out | std::ofstream::binary);
			if (!file.is_open()) {
				throw std::runtime_error(std::string("unable to open file for writing: ") + v.first + " path=" + dst.string());
			}

			auto d = v.second.cont_();
			std::copy(d.begin(), d.end(), std::ostream_iterator<unsigned char>{file});
			file.flush();
		}
		else if (v.second.t_ == item::t_folder) {
			assert(!src_root.empty());
			fs::path src = (src_root / v.second.src_);

			fs::create_directories(dst);

			copy_dir(dst, src);
		}
		else if (v.second.t_ == item::t_file) { //copy file
			assert(!src_root.empty());
			//create folder
			fs::create_directories(dst.branch_path());

			fs::path src = (src_root / v.second.src_);

			try {
				fs::remove(dst);
			}
			catch( const std::exception& )
			{}

			fs::copy_file(src, dst);
		}
	}
}

