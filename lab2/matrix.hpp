#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <complex>

template<class T>
class Matrix {
    public:
        Matrix(T ** item, int n){
            mat = ArraySequence<ArraySequence<T> >(n);
            for(int i = 0; i < n; i++) {
                ArraySequence<T> ptr(item[i], n);
                mat.Set(i, ptr);
            }
            dim = n;
        }
        Matrix() {
            mat = ArraySequence<ArraySequence<T> >();
            dim = 0;
        }
        Matrix(int n){
            mat = ArraySequence<ArraySequence<T> >(n);
            for(int i = 0; i < n; i++) {
                ArraySequence<T> ptr(n);
                mat.Set(i, ptr);
            }
            dim = n;
        }
        Matrix(const Matrix<T> & matr){
            mat = ArraySequence<ArraySequence<T> >(matr.GetDim());
            for(int i = 0; i < matr.GetDim(); i++) {
                ArraySequence<T>  ptr = (matr.mat.Get(i));
                mat.Set(i, ptr);
            }
            dim = matr.GetDim();
        }
        int GetDim() const{
            return dim;
        }
        T Get(int i, int j) const{
            return mat.Get(i).Get(j);
        }
        void Set(int i, int j,const T& item){
            ArraySequence< T > ptr = mat.Get(i);
            ptr.Set(j, item);
            mat.Set(i,ptr);
        }
        Matrix<T> * Sum(const Matrix<T>& a) const{
            if(a.GetDim() != dim) {
                throw "Error dimention matrix";
            }
            Matrix<T> * ptr = new Matrix<T>(dim);
            for(int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                    ptr->Set(i, j, Get(i,j) + a.Get(i,j));
                }
            }
            return ptr;
        }
        Matrix<T> * Scalar(const T& a) const{
            Matrix<T> * ptr = new Matrix<T>(dim);
            for(int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                    ptr->Set(i, j, Get(i,j) * a);
                }
            }
            return ptr;
        }
        double norm() const{
            double p;
            for(int i = 0; i < dim; i++){
                double sum;
                for(int j = 0; j < dim; j++){
                    sum += std::abs(Get(j,i));
                }
                if(sum >= p){
                    p = sum;
                }
            }
            return p;
        }
    private:
        int dim;
        ArraySequence<ArraySequence<T> > mat;
};
template<class T>
const Matrix<T> operator + (const Matrix<T>& left, const Matrix<T>& right) {
        return (*(left.Sum(right)));
    }
template<class T>
const Matrix<T> operator * (const Matrix<T>& left, const T& a) {
        return (*(left.Scalar(a)));
}


#endif