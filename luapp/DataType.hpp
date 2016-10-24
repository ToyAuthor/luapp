
#ifndef _LUAPP_DATA_TYPE_HPP_
#define _LUAPP_DATA_TYPE_HPP_


namespace lua{

//------Only the following date types could work in luapp------
typedef bool            Bool;
typedef double          Num;
typedef int             Int;
typedef std::string     Str;
typedef void*           Ptr;


// As null. Not test yet.
class Nil
{
	public:

		Nil(){}
		~Nil(){}
};

}//namespace lua

#endif//_LUAPP_STATE_HPP_
