#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
	    int nelem;
	    BSNode<T> *root;

	    //Busqueda elem
	    BSNode<T>* search(BSNode<T>* n, T e) const{
	    	if(n==NULL){
			throw std::runtime_error("Elemento no encontrado en el árbol");
		}else if(n->elem < e){
			return search(n->right,e);
		}else if(n->elem> e){
			return search(n->left,e);
		}else{
			return n;
		}
	    }

	    //Inserción elem
	    BSNode<T>* insert(BSNode<T>* n, T e){
	    	if(n== NULL){
			++nelem;
			return new BSNode<T>(e);
		}
		if(n->elem == e){
			throw std::runtime_error("No se ha podido insertar en el árbol");
		}else if(n->elem < e){
			n->right = insert(n->right,e);
		}else{
			n->left = insert (n->left,e);
		}
		return n; 
	    }

	    //Recorrido e impresión del arbol
	    void print_inorder(std::ostream &out, BSNode<T>* n) const{
		    if (n != NULL) {
			    print_inorder(out, n->left);
			    out << n->elem << " ";
			    print_inorder(out, n->right);
		    }
	    }

	    //Eliminación elem
	    BSNode<T>* remove_max(BSNode<T>* n){
                if (n->right == NULL){
			BSNode<T>* temp = n->left;
			delete n;
			--nelem;
			return temp;
                }else{
                        n->right = remove_max(n->right);
                        return n;
                }
            }

	    BSNode<T>* remove(BSNode<T>* n, T e){
		    if (n == NULL) {
		    	throw std::runtime_error("Elemento no encontrado");
		    }else if (e < n->elem) {
		    	n->left = remove(n->left, e);
		    }else if (e > n->elem) {
		    	n->right = remove(n->right, e);
		    }else{
		    	if (n->left == NULL && n->right == NULL) {
				delete n;
				--nelem;
				return nullptr;
			}else if (n->left == NULL) {
				BSNode<T>* temp = n->right;
				delete n;
				--nelem;
				return temp;
			}else if (n->right == nullptr){
				BSNode<T>* temp = n->left;
				delete n;
				--nelem;
				return temp;
			}else{
				n->elem = max(n->left);
				n->left = remove_max(n->left);
			}
		    }
		    return n;
	    }

	    T max(BSNode<T>* n) const{
	    	if (n == NULL) {
                        throw std::runtime_error("Elemento no encontrado");
		}else if(n->right != NULL){
			return max(n->right);
		}else{
			return n->elem;
		}
	    }

	    //Destrucción
	    void delete_cascade(BSNode<T>* n){
	    	if (n != NULL) {
			delete_cascade(n->left);
			delete_cascade(n->right);
			delete n;
		}
	    }

    public:
	    //Creación y tamaño
	    BSTree(): nelem(0),root(NULL){}
	    int size() const{
	    	return nelem;
	    }

	    //Busqueda elem
	    T search(T e) const{
	    	BSNode<T>* result= search(root,e);
		return result-> elem;
	    }
	    T operator[](T e) const{
	    	return search(e);
	    }

	    //Inserción elementos
	    void insert(T e){
	    	root= insert(root,e);
	    }

	    //Sobrecarga <<
	    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
		    bst.print_inorder(out, bst.root);
		    return out;
	    }

	    //Eliminación de elem
	    void remove(T e){
		    root = remove(root, e);
	    }

	    //Destrucción
	     ~BSTree(){
		     delete_cascade(root);
	     }

    
};

#endif
