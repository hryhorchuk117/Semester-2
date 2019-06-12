#pragma once

#include "point.h"
#include "list.h"
#include "vector.h"
#include "binaryTree.h"
#include "avl.h"


template <class type>
double testAdd(type&, int);

template <class type>
double testFind(type&, point);

template <class type>
double testFindMist(type&, point, double);

template <class type, class vec>
double testFindTree(type&, point, vec&);

template <class type, class vec>
double testFindMistTree(type&, point, vec&, double);

template <class type>
double testErase(type&, point);

template <class type>
double testPrint(type&);

void benchmark(int);