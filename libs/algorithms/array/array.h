# ifndef INC_ARRAY_H
# define INC_ARRAY_H

# include <stddef.h>


// ввод массива data размера n
extern void inputArray_ (int *a , size_t n ) ;
// вывод массива data размера n
extern void outputArray_ ( const int *a , size_t n ) ;

// возвращает значение первого вхождения элемента x
// в массиве a размера n при его наличии, иначе - n
extern size_t linearSearch_ ( const int *a , const size_t n , int x ) ;

// возвращает позицию вхождения элемента x
// в отсортированном массиве a размера n при его наличии, иначе - SIZE_MAX
extern size_t binarySearch_ ( const int *a , const size_t n , int x ) ;
// возвращает позицию первого элемента равного или большего x
// в отсортированном массиве a размера n
// при отсутствии такого элемента возвращает n
extern size_t binarySearchMoreOrEqual_ ( const int *a , const size_t n , int x ) ;

// вставка элемента со значением value
// в массив data размера n на позицию pos
extern void insert_ (int *a , size_t *n , size_t pos , int value ) ;

// добавление элемента value в конец массива data размера n
extern void append_ (int *a , size_t *n , int value ) ;

// удаление из массива data размера n элемента на позиции pos
// с сохранением порядка оставшихся элементов
extern void deleteByPosSaveOrder_ (int *a , size_t *n , size_t pos ) ;

// удаление из массива data размера n элемента на позиции pos
// без сохранения порядка оставшихся элементов
// размер массива data уменьшается на единицу
extern void deleteByPosUnsaveOrder_ (int *a , size_t *n , size_t pos ) ;

// возвращает значение ’истина’ если все элементы
// массива data размера n соответствует функции-предикату predicate
// иначе - ’ложь’
extern int all_ ( const int* a , size_t n , int (* predicate ) (int) ) ;

// возвращает значение ’истина’ если хотя бы один элемент
// массива data размера n соответствует функции-предикату predicate
// иначе - ’ложь’
extern int any_ ( const int *a , size_t n , int (* predicate ) (int) ) ;

// применяет функцию predicate ко всем элементам массива source
// размера n и сохраняет результат в массиве dest размера n
extern void forEach_ ( const int * source , int * dest , size_t n , const int (*
predicate ) ( int) ) ;

// возвращает количество элементов массива data размера n
// удовлетворяющих функции-предикату predicate
extern int countIf_ ( const int * a , size_t n , int (* predicate ) (int) ) ;

// удаляет из массива data размера n все элементы, удовлетворяющие
// функции-предикату deletePredicate, записывает в n новый размер
// массива
extern void deleteIf_ (int * a , size_t * n , int (* deletePredicate ) (int) ) ;

# endif
