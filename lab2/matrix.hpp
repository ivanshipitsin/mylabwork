#ifndef MATRIX_HPP
#define MATRIX_HPP

template<class T>
class Matrix {
    public:
        Matrix(T ** item, int n){
            mat = new ArraySequence<ArraySequence<T> *>(n);
            for(int i = 0; i < n; i++) {
                ArraySequence<T> * ptr = new ArraySequence<T>(item[i], n);
                mat->Set(i, ptr);
            }
            dim = n;
        }
        Matrix() {
            mat = nullptr;
            dim = 0;
        }
        Matrix(int n){
            mat = new ArraySequence<ArraySequence<T> *>(n);
            for(int i = 0; i < n; i++) {
                ArraySequence<T> * ptr = new ArraySequence<T>(n);
                mat->Set(i, ptr);
            }
            dim = n;
        }
        Matrix(const Matrix<T> & matr){
            mat = new ArraySequence<ArraySequence<T> *>(matr.GetDim());
            for(int i = 0; i < matr.GetDim(); i++) {
                ArraySequence<T> * ptr = new ArraySequence<T>();
                *ptr = *(matr.mat->Get(i));
                mat->Set(i, ptr);
            }
            dim = matr.GetDim();
        }
        int GetDim() const{
            return dim;
        }
        T Get(int i, int j) const{
            return mat->Get(i)->Get(j);
        }
        void Set(int i, int j,const T& item){
            mat->Get(i)->Set(j,item);
        }
        Matrix<T> * Sum(const Matrix<T>& a) const{
            if(a.GetDim() != dim) {
                throw "Error dimention matrix";
            }
            Matrix<T> * ptr = new Matrix<T>(dim);
            for(int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                    ptr->Set(i, j, mat->Get(i)->Get(j) + a.Get(i,j));
                }
            }
            return ptr;
        }
        Matrix<T> * Scalar(const T& a) const{
            Matrix<T> * ptr = new Matrix<T>(dim);
            for(int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                    ptr->mat->Get(i)->Set(j, mat->Get(i)->Get(j) * a);
                }
            }
            return ptr;
        }
        ~Matrix(){
            try{
                for (int i = 0; i < dim; i++){
                    if(mat->Get(i)){
                        delete mat->Get(i);
                    }
                }
            }
            catch(std::string a){
                std::cout << "Ohhh . " << a;
            }
            if(mat){
                delete mat;
            }
        }

    private:
        int dim;
        ArraySequence<ArraySequence<T> *> * mat;
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