/**
 * @file
 * @ingroup Math
 * Found from http://www.cplusplus.com/forum/general/8147/
 */
#ifndef BB_PROPERTY_H
#define BB_PROPERTY_H
namespace BaconBox{
	template<class _Prop_t,
	class _ObjClass_t>
	class Property
	{
		typedef _Prop_t (_ObjClass_t::* _pmGet_t)() const;
		typedef void (_ObjClass_t::* _pmSet_t)(_Prop_t);
		
		_ObjClass_t* m_objInstance;
		_pmGet_t     m_pmGet;
		_pmSet_t     m_pmSet;
		
	public:
		void setInstance(_ObjClass_t* instance){m_objInstance = instance;}
		Property(_ObjClass_t* objInstance, _pmGet_t pmGet, _pmSet_t pmSet)
		:  m_objInstance(objInstance), m_pmGet(pmGet), m_pmSet(pmSet)
		{}
		operator _Prop_t() { return (m_objInstance->*m_pmGet)(); }
		void operator =(_Prop_t value) { (m_objInstance->*m_pmSet)(value); }
	};
}
#endif
