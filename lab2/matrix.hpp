#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <complex>

template<class T>
class Matrix {
    public:
        Matrix(T * item, int n){
            mat = new ArraySequence<T>(item,n*n);
            dim = n;
        }
        Matrix() {
            mat = new ArraySequence<T>();
            dim = 0;
        }
        Matrix(int n){
            mat = new ArraySequence<T>(n*n);
            dim = n;
        }
        Matrix(const Matrix<T> & matr){
            dim = matr.GetDim();
            mat = new ArraySequence<T>(*(matr.mat));
        }
        int GetDim() const{
            return dim;
        }
        T Get(int i, int j) const{
            return mat->Get(i * dim + j);
        }
        void Set(int i, int j,const T& item){
            mat->Set(i*dim + j, item);
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
                double sum = 0;
                for(int j = 0; j < dim; j++){
                    sum += std::abs(Get(j,i));
                }
                if(sum >= p){
                    p = sum;
                }
            }
            return p;
        }
        void clear(){
            delete mat;
        }
        
    private:
        int dim;
        ArraySequence<T>* mat;
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