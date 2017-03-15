#ifndef _CORE_CONSTRUCTOR_INLINE_
#define _CORE_CONSTRUCTOR_INLINE_

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace constructor { // gsystem.detail.constructor

template <typename ClassT>
GINLINE gvoid _GDefaultConstruct(ClassT *ptr, GTrueType)
{
	// û��Ĭ�ϵĹ��캯����������
}

template <typename ClassT>
GINLINE gvoid _GDefaultConstruct(ClassT *ptr, GFalseType)
{
	// ��Ĭ�ϵĹ��캯��������Ĭ�ϵĹ��캯��
	new(ptr)ClassT();
}

template <typename ClassT>
GINLINE gvoid __GCopyConstruct(ClassT *ptr, const ClassT &copyable, GTrueType)
{
	// �����������ڱ��������Ż������õȺŲ���Ч�ʽϸ�
	*ptr = copyable;
}

template <typename ClassT>
GINLINE gvoid __GCopyConstruct(ClassT *ptr, const ClassT &copyable, GFalseType)
{
	// �ǻ������͵����ڴ濽��
	GMemCopy(ptr, &copyable);
}

template <typename ClassT>
GINLINE gvoid _GCopyConstruct(ClassT *ptr, const ClassT &copyable, GTrueType)
{
	// û�п������캯������ʱ������������ǣ�����������Ϊû�п������캯����
	__GCopyConstruct(ptr, copyable,
		GTypeTraits<ClassT>::Arithmetic());
}

template <typename ClassT>
GINLINE gvoid _GCopyConstruct(ClassT *ptr, const ClassT &copyable, GFalseType)
{
	// �п������캯�������ÿ������캯��
	new(ptr)ClassT(copyable);
}

template <typename ClassT>
GINLINE gvoid __GMoveConstruct(ClassT *ptr, ClassT &&moveable, GTrueType)
{
	// �����������ڱ��������Ż������õȺŲ���Ч�ʽϸ�
	*ptr = moveable;
}

template <typename ClassT>
GINLINE gvoid __GMoveConstruct(ClassT *ptr, ClassT &&moveable, GFalseType)
{
	// �ǻ������͵����ڴ濽��
	GMemCopy(ptr, &moveable);
}

template <typename ClassT>
GINLINE gvoid _GMoveConstruct(ClassT *ptr, ClassT &&moveable, GTrueType)
{
	// û���ƶ����캯������ʱ������������ǣ�����������Ϊû���ƶ����캯����
	__GMoveConstruct(ptr, GForward<ClassT>(moveable),
		GTypeTraits<ClassT>::Arithmetic());
}

template <typename ClassT>
GINLINE gvoid _GMoveConstruct(ClassT *ptr, ClassT &&moveable, GFalseType)
{
	// ���ƶ����캯���������ƶ����캯�������ܻ��˻�Ϊ�������캯��
	new(ptr)ClassT(GForward<ClassT>(moveable));
}

template <typename ClassT>
GINLINE gvoid _GDestruct(ClassT *ptr, GTrueType)
{

}

template <typename ClassT>
GINLINE gvoid _GDestruct(ClassT *ptr, GFalseType)
{
	ptr->~ClassT();
}


}  // namespace gsystem.detail.constructor
}  // namespace gsystem.detail
}  // namespace gsystem

namespace gsystem { // gsystem

template <typename ClassT, typename... ArgsT>
GINLINE gvoid GConstruct(ClassT *ptr, ArgsT&& ...args)
{
	new(ptr) ClassT(GForward<ArgsT>(args)...);
}

template <typename ClassT> 
GINLINE gvoid GConstruct(ClassT *ptr)
{
	GDefaultConstruct(ptr);
}

template <typename ClassT>
GINLINE gvoid GConstruct(ClassT *ptr, const ClassT &copyable)
{
	GCopyConstruct(ptr, copyable);
}

template <typename ClassT>
GINLINE gvoid GConstruct(ClassT *ptr, ClassT &&moveable)
{
	GMoveConstruct(ptr, GForward<ClassT>(moveable));
}

template <typename ClassT>
GINLINE gvoid GDestruct(ClassT *ptr)
{
	detail::constructor::_GDestruct(ptr,
		GTypeTraits<ClassT>::TrivialDestructible());
}

template <typename ClassT> 
GINLINE gvoid GDefaultConstruct(ClassT *ptr)
{
	static_assert(GIsDefaultConstructible<ClassT>::value,
		"this type has not a default constructor.");
	detail::constructor::_GDefaultConstruct(ptr,
		GTypeTraits<ClassT>::TrivialDefaultConstructible());
}

template <typename ClassT> 
GINLINE gvoid GCopyConstruct(ClassT *ptr, const ClassT &copyable)
{
	static_assert(GIsCopyConstructible<ClassT>::value,
		"this type has not a copy constructor.");
	detail::constructor::_GCopyConstruct(ptr, copyable,
		GTypeTraits<ClassT>::TrivialCopyConstructible());
}

template <typename ClassT> 
GINLINE gvoid GMoveConstruct(ClassT *ptr, ClassT &&moveable)
{
	static_assert(GIsMoveConstructible<ClassT>::value,
		"this type has not a move constructor.");
	detail::constructor::_GMoveConstruct<ClassT>(ptr, GForward<ClassT>(moveable),
		GTypeTraits<ClassT>::TrivialMoveConstructible());
}

} // namespace gsystem

#endif // _CORE_CONSTRUCTOR_INLINE_