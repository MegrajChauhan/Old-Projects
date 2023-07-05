#ifndef FART_CONTAINER
#define FART_CONTAINER

#include<string>
#include <vector>
#include <utility>

//the array for holding single items
template <typename _Type>
class Fart_arr
{
	std::vector<_Type> _box_;
	int size = 0;

public:
	Fart_arr(_Type _val_) : _box_{_val_}, size{1} {}
	Fart_arr(std::initializer_list<_Type> _arr_) : _box_{_arr_}{size = _box_.size();}
	Fart_arr() = default;

	int get_size()
	{
		return size;
	}

	_Type &operator[](int index)
	{
		return _box_[index];
	}

	void operator=(_Type _val_)
	{
		_box_.push_back(_val_);
		size++;
	}
    
	void operator=(std::initializer_list<_Type>& hr)
	{
		_box_.push_back(hr);
		size = _box_.size();
	}

	// void operator=(Fart_arr<_Type>& tt)
	// {
	// 	_box_ = tt.get_box();
	// 	size = tt.get_size();
	// }

	void push(_Type _to_push)
	{
		_box_.push_back(_to_push);
		size++;
	}

	_Type get_val(int pos)
	{
		return _box_[pos];
	}

	bool is_there(_Type _search_)
	{
		for (_Type t : _box_)
		{
			if (t == _search_)
				return true;
		}
		return false;
	}

	int position_of(_Type _to_find)
	{
		int p = 0;
		for (_Type t : _box_)
		{
			if (t == _to_find)
				return p;
			p++;
		}
		if (p >= size)
			return 0;
		return p;
	}

	_Type *begin()
	{
		return &_box_[0];
	}

	_Type *end()
	{
		return &_box_[size];
	}

	int occurences(_Type to_look)
	{
		int count = 0;
		for (_Type t : _box_)
		{
			if (t == to_look)
				count++;
		}
		return count;
	}

	int position_after(int po, _Type to_look)
	{
		int posi = 0;
		for (int i = po + 1; i < _box_.size(); i++)
		{
			if (_box_[i] == to_look)
				return posi;
			posi++;
		}
		return 0;
	}

    bool is_there_c(char c)
	{
		std::string temp;
		temp += c;
		return is_there(temp);
	}

	void pop(int po)
	{
		std::vector<_Type> _temp;
		for (_Type t : _box_)
		{
			if (t == _box_[po])
				continue;
			else
				_temp.push_back(t);
		}
		_box_.clear();
		_box_ = _temp;
		size = _temp.size();
		_temp.clear();
	}

	void pop_back()
	{
		_box_.pop_back();
		size--;
	}

	void clear(_Type val)
	{
		_box_.clear();
		_box_.push_back(val);
	}
};

//the array for holding a key and a value
template <typename _key, typename _val>
class Fart_pair
{

public:
    
    void reset( int position, _key new_key, _val new_val)
	{
		_box_[position] = std::make_pair(new_key, new_val);
	}

	void swap(int p1, int p2)
	{
		std::pair<_key, _val> a1 = _box_[p1];
		std::pair<_key, _val> a2 = _box_[p2];
		_box_[p1] = a2;
		_box_[p2] = a1;
	}

	int get_size()
	{
		return size;
	}

	std::vector<std::pair<_key, _val>> &get_box()
	{
		return _box_;
	}

	std::pair<_key, _val> &operator[](int index)
	{
		return _box_[index];
	}

	void operator=(std::pair<_key, _val> _val_)
	{
		_box_.push_back(_val_);
		size++;
	}

	void operator=(std::initializer_list<std::pair<_key, _val>> & arr)
	{
		_box_ = arr;
	}

	void push(std::pair<_key, _val> _to_push)
	{
		_box_.push_back(_to_push);
		size++;
	}

	void push(_key k, _val v)
	{
		_box_.push_back(std::make_pair(k, v));
		size++;
	}

	_val get_val(int pos)
	{
		return _box_[pos].second;
	}

    _key get_key(int pos)
	{
      return _box_[pos].first;
	}
   
	bool is_there(std::pair<_key, _val> _search_)
	{
		for (std::pair<_key, _val> t : _box_)
		{
			if (t.first == _search_.first && t.second == _search_.second)
				return true;
		}
		return false;
	}

	bool is_there_val(_val _search_)
	{
		for (std::pair<_key, _val> t : _box_)
		{
			if (t.second == _search_)
				return true;
		}
		return false;
	}
    
	bool is_there_(char c)
	{
		std::string temp;
		temp += c;
		return is_there_val(temp);
	}

	bool is_there(_key k, _val v)
	{
		for (std::pair<_key, _val> t : _box_)
		{
			if (t.first == k && t.second == v)
				return true;
		}
		return false;
	}

	bool is_there(_key _search_)
	{
		for (std::pair<_key, _val> t : _box_)
		{
			if (t.first == _search_)
				return true;
		}
		return false;
	}

	int position_of(std::pair<_key, _val> _to_find)
	{
		int p = 0;
		for (std::pair<_key, _val> t : _box_)
		{
			if (t.first == _to_find.first && t.second == _to_find.second)
				return p;
			p++;
		}
		if (p >= size)
			return 0;
		return p;
	}

	int position_of(_key _to_find, _val to_find)
	{
		int p = 0;
		for (std::pair<_key, _val> t : _box_)
		{
			if (t.first == _to_find && t.second == to_find)
				return p;
			p++;
		}
		if (p >= size)
			return 0;
		return p;
	}

	int position_of(_key _to_find)
	{
		int p = 0;
		for (std::pair<_key, _val> t : _box_)
		{
			if (t.first == _to_find)
				return p;
			p++;
		}
		if (p >= size)
			return 0;
		return p;
	}

	int position_of_val(_val _to_find)
	{
		int p = 0;
		for (std::pair<_key, _val> t : _box_)
		{
			if (t.second == _to_find)
				return p;
			p++;
		}
		if (p >= size)
			return 0;
		return p;
	}

	std::pair<_key, _val> *begin()
	{
		return &_box_[0];
	}

	std::pair<_key, _val> *end()
	{
		return &_box_[size];
	}

	int occurences(std::pair<_key, _val> to_look)
	{
		int count = 0;
		for (std::pair<_key, _val> t : _box_)
		{
			if (t.first == to_look.first && t.second == to_look.second)
				count++;
		}
		return count;
	}

	int occurences(_key to_look, _val _to_look)
	{
		int count = 0;
		for (std::pair<_key, _val> t : _box_)
		{
			if (t.first == to_look && t.second == _to_look)
				count++;
		}
		return count;
	}

    std::vector<int> array_of_occurences(_key to_look)
	{
	  std::vector<int> posi_arr;
		for (int i = 0;i < _box_.size(); i++)
		{
			if (_box_[i].first == to_look)
			{
              posi_arr.push_back(i);
			}
		}
		return posi_arr;
	}

	 std::vector<int> array_of_occurences(_key to_look, _val _to_look)
	{
	  std::vector<int> posi_arr;
		for (int i = 0;i < _box_.size(); i++)
		{
			if (_box_[i].first == to_look && _box_[i].second == _to_look)
			{
              posi_arr.push_back(i);
			}
		}
		return posi_arr;
	}

	 std::vector<int> array_of_occurences(std::pair<_key, _val> pair)
	{
	  std::vector<int> posi_arr;
		for (int i = 0;i < _box_.size(); i++)
		{
			if (_box_[i] == pair)
			{
              posi_arr.push_back(i);
			}
		}
		return posi_arr;
	}

	 std::vector<int> array_of_occurences(_val _to_look)
	{
	  std::vector<int> posi_arr;
		for (int i = 0;i < _box_.size(); i++)
		{
			if (_box_[i].second == _to_look)
			{
              posi_arr.push_back(i);
			}
		}
		return posi_arr;
	}

	int occurences(_key to_look)
	{
		int count = 0;
		for (std::pair<_key, _val> t : _box_)
		{
			if (t.first == to_look)
				count++;
		}
		return count;
	}

	int position_after(int po, std::pair<_key, _val> to_look)
	{
		int posi = 0;
		for (int i = po + 1; i < _box_.size(); i++)
		{
			if (_box_[i].first == to_look.first && _box_[i].second == to_look.second)
				return posi;
			posi++;
		}
		return 0;
	}

	int position_after(int po, _key k, _val v)
	{
		int posi = 0;
		for (int i = po + 1; i < _box_.size(); i++)
		{
			if (_box_[i].first == k && _box_[i].second == v)
				return posi;
			posi++;
		}
		return 0;
	}

	void pop(int po)
	{
		std::vector<std::pair<_key, _val>> _temp;
		for (std::pair<_key, _val> t : _box_)
		{
			if (t.first == _box_[po].first)
				continue;
			else
				_temp.push_back(t);
		}
		_box_.clear();
		_box_ = _temp;
		size = _temp.size();
		_temp.clear();
	}

	void pop_back()
	{
		_box_.pop_back();
		size--;
	}
	private:
	std::vector<std::pair<_key, _val>> _box_;
	int size = 0;
	public:
    Fart_pair(std::pair<_key, _val> _val_) : _box_{_val_}, size{1} {}
	Fart_pair(std::initializer_list<std::pair<_key, _val>> _arr_) : _box_{_arr_}{size = _box_.size();}
	Fart_pair(Fart_pair<_key, _val> &_cont_){
             this->_box_ = _cont_.get_box(); 
			 this->size = _cont_.get_size();
	}
    Fart_pair() = default;
};

#endif
