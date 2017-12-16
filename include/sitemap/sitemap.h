#ifndef H_FE2339F9FB6D4108B0A349243242C10C
#define H_FE2339F9FB6D4108B0A349243242C10C

#include <functional>
#include <vector>
#include <map>
#include <utility>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

namespace fs = boost::filesystem;

struct sitemap
{
	typedef boost::filesystem::path path;

	struct folder
	{
		std::string p_;
		explicit folder(const std::string& p)
			:p_(p)
		{}
	};

	typedef std::function<std::vector<unsigned char>()> content;


	struct item
	{
		enum type
		{
			t_folder
			,t_file
			,t_content
			,t_undef
		};

		type t_;

		path dst_;
		path src_;
		content cont_;

		item(const folder& dst, const folder& src)
			:t_(t_folder)
			,dst_(dst.p_)
			,src_(src.p_)
		{}
		item(const std::string& dst, const std::string& src_file)
			:t_(t_file)
			,dst_(dst)
			,src_(src_file)
		{}
		item(const std::string& dst, content c)
			:t_(t_content)
			,dst_(dst)
			,cont_(c)
		{}
		item(const std::string& dst)
			:t_(t_content)
			,dst_(dst)
		{}

		item& operator=(const item&) = delete;
	};

	typedef std::map<std::string, item> items;

	items i_;
	path root_;

	void set_root(const path& r)
	{
		root_ = r;
	}

	/*
	void operator +=(const std::pair<std::string, item>& v)
	{
		i_.insert(v);
	}
	*/

	struct setter
	{
		const std::string& n_;
		items* i_;

		setter(const std::string& n, items& i)
			:n_(n)
			,i_(&i)
		{}

		setter& operator=(item i)
		{
			if (i_->find(n_) != i_->end())
				throw std::runtime_error(std::string("Item already exists:") + n_);
			i_->insert({n_, std::move(i)});
			return *this;
		}
		setter& operator=(content c)
		{
			auto it = i_->find(n_);
			if (it == i_->end())
				throw std::runtime_error(std::string("Item not found:") + n_);
			it->second.cont_ = c;
			return *this;
		}

		const std::string dst() const
		{
			auto it = i_->find(n_);
			if (it == i_->end())
				throw std::runtime_error(std::string("Item not found:") + n_);
			if (it->second.dst_.stem() == "index")
			{
				std::string p = it->second.dst_.parent_path().string();
				if (!p.empty() && p[p.size()-1] != '/') {
					p += "/";
				}
				return p;
			}
			return it->second.dst_.string();
		}


	};

	setter operator[](const std::string& n)
	{
		return setter(n, i_);
	}

	void generate(const path& src_root);
};

#endif
