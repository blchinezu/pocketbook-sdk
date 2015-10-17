/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISTREE_H
#define PBSYNOPSISTREE_H

#include <inkview.h>
#include "pbsynopsisdefines.h"

template <class TType>
class PBSynopsisTree
{
public:
	PBSynopsisTree();
	PBSynopsisTree(int type, int level);

	virtual ~PBSynopsisTree();

	void SetType(int type);
	int GetType();
	void SetLevel(int level);
	int GetLevel();
	void SetVisible(int visible);
	int GetVisible();

	TType* SetParent(TType *NewItem);
	TType* SetChild(TType *NewItem);
	TType* SetNext(TType *NewItem);
	TType* SetPrev(TType *NewItem);
	TType* GetParent();
	TType* GetChild();
	TType* GetChildM(int mask);
	TType* GetNext();
	TType* GetNextV(int visible);
	TType* GetNextM(int mask);
	TType* GetNextVM(int visible, int mask);
	TType* GetPrev();
	TType* GetPrevV(int visible);
	TType* GetBelow();
	TType* GetBelowM(int mask);
	TType* GetBelowVM(int visible, int mask);
	TType* GetAbove();
	TType* GetAboveVM(int visible, int mask);
	TType* GetFollow();

	void DestroyChildren();

protected:
	TType *m_pParent, *m_pChild, *m_pNext, *m_pPrev;
	int m_Type;
	int m_Level;
	int m_Visible;
};

template <class TType>
PBSynopsisTree<TType>::PBSynopsisTree():
		m_pParent(NULL),
		m_pChild(NULL),
		m_pNext(NULL),
		m_pPrev(NULL),
		m_Type(0),
		m_Level(0),
		m_Visible(0)
{
}

template <class TType>
PBSynopsisTree<TType>::PBSynopsisTree(int type, int level):
		m_pParent(NULL),
		m_pChild(NULL),
		m_pNext(NULL),
		m_pPrev(NULL),
		m_Type(type),
		m_Level(level),
		m_Visible(1)
{
}

template <class TType>
PBSynopsisTree<TType>::~PBSynopsisTree()
{
}

template <class TType>
void PBSynopsisTree<TType>::SetType(int type)
{
	m_Type = type;
}

template <class TType>
int PBSynopsisTree<TType>::GetType()
{
	return m_Type;
}

template <class TType>
void PBSynopsisTree<TType>::SetLevel(int level)
{
	m_Level = level;
}

template <class TType>
int PBSynopsisTree<TType>::GetLevel()
{
	return m_Level;
}

template <class TType>
void PBSynopsisTree<TType>::SetVisible(int visible)
{
	m_Visible = visible;
}

template <class TType>
int PBSynopsisTree<TType>::GetVisible()
{
	return m_Visible;
}

template <class TType>
TType *PBSynopsisTree<TType>::SetParent(TType *NewItem)
{
	m_pParent = NewItem;
	return m_pParent;
}

template <class TType>
TType *PBSynopsisTree<TType>::SetChild(TType *NewItem)
{
	m_pChild = NewItem;
	return m_pChild;
}

template <class TType>
TType *PBSynopsisTree<TType>::SetNext(TType *NewItem)
{
	m_pNext = NewItem;
	return m_pNext;
}

template <class TType>
TType *PBSynopsisTree<TType>::SetPrev(TType *NewItem)
{
	m_pPrev = NewItem;
	return m_pPrev;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetParent()
{
	return m_pParent;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetChild()
{
	return m_pChild;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetChildM(int mask)
{
	TType *item = m_pChild;

	if (item != NULL && ((item->GetType() & mask) == 0))
		item = item->GetNextM(mask);

	return item;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetNext()
{
	return m_pNext;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetNextV(int visible)
{
	TType *item = m_pNext;

	while (item != NULL && item->GetVisible() != visible)
		item = item->GetNext();

	return item;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetNextM(int mask)
{
	TType *item = m_pNext;

	while (item != NULL && ((item->GetType() & mask) == 0))
		item = item->GetNext();

	return item;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetNextVM(int visible, int mask)
{
	TType *item = m_pNext;

	while (item != NULL && (item->GetVisible() != visible || ((item->GetType() & mask) == 0)))
		item = item->GetNext();

	return item;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetPrev()
{
	return m_pPrev;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetPrevV(int visible)
{
	TType *item = m_pPrev;

	while (item != NULL && item->GetVisible() != visible)
		item = item->GetPrev();

	return item;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetBelow()
{
	if (this->GetChild() != NULL)
		return this->GetChild();

	if (this->GetNext() != NULL)
		return this->GetNext();

	if (this->GetParent() != NULL)
	{
		TType *tmp = this->GetParent();
		while (tmp->GetNext() == NULL && tmp->GetParent() != NULL)
			tmp = tmp->GetParent();
		return tmp->GetNext();
	}

	return NULL;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetBelowM(int mask)
{
	TType *item = this->GetBelow();

	while (item != NULL && ((item->GetType() & mask) == 0))
		item = item->GetBelow();

	return item;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetBelowVM(int visible, int mask)
{
	TType *item = this->GetBelow();

	while (item != NULL && (item->GetVisible() != visible || ((item->GetType() & mask) == 0)))
		item = item->GetBelow();

	return item;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetAbove()
{
	if (this->GetPrev() != NULL)
	{
		if ((this->GetPrev())->GetChild() == NULL)
			return this->GetPrev();
		TType *tmp = this->GetPrev()->GetChild();
		while (tmp != NULL && tmp->GetBelow() != this)
			tmp = tmp->GetBelow();
		return tmp;
	}

	if (this->GetParent() != NULL)
	{
		return this->GetParent();
	}

	return NULL;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetAboveVM(int visible, int mask)
{
	TType *item = this->GetAbove();

	while (item != NULL && (item->GetVisible() != visible || ((item->GetType() & mask) == 0)))
		item = item->GetAbove();

	return item;
}

template <class TType>
TType *PBSynopsisTree<TType>::GetFollow()
{
	return GetBelow();
}

template <class TType>
void PBSynopsisTree<TType>::DestroyChildren()
{
	TType *Current = m_pChild;
	TType *tmp;
	while (Current != NULL){
		Current->DestroyChildren();
		if (Current->GetNext() != NULL)
		{
			tmp = Current;
			Current = Current->GetNext();
			delete(tmp);
		} else {
			delete(Current);
			Current = NULL;
		}
	}
}

#endif // PBSYNOPSISTREE_H
