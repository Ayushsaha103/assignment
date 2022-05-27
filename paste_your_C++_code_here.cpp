

// This program has a simple user-defined Vect class and an iterator over that class
//------------------------------------------------

#include<iostream>
#include<vector>

class VectItr;
class Vect;
class MatrixRowItr;
class Matrix;
class ColOnlyVectItr;
class ColOnlyVect;

class ConstVectItr;

//--------------------- Vect Class ---------------------------
class Vect {
protected:
	std::vector<int> vect;
public:
	Vect(std::vector<int>& thi) : vect(thi) {}
	Vect(int numelems) { vect.clear(); for (int i = 0;i < numelems; i++) vect.push_back(0); }
	Vect(int numelems, int value) { vect.clear(); for (int i = 0;i < numelems; i++) vect.push_back(value); }

	VectItr begin();// { return VectItr(*this, 0); }
	VectItr end();// { return VectItr(*this, int(vect.size())); }
	int& at(int index);// { return vect.at(index); }
	int& operator[](int index);
	int size() { return vect.size(); }
	Vect& make_reference_Vect() { return (*this); }
	Vect& operator+=(int amt);
	Vect& operator-=(int amt);
	Vect& operator*=(int amt);
	Vect& operator-();
	// Vect& operator*(int lhs, Vect& rhs);
	Vect& operator=(Vect& rhs);
	Vect operator*(int amt);
	Vect operator-(int amt);
	Vect operator+(int amt);
	friend Vect operator+(int amt, Vect& rhs);
	friend Vect operator-(int amt, Vect& rhs);
	friend Vect operator*(int amt, Vect& rhs);
	
	friend Vect operator*(Vect& lhs, Vect& rhs);
	friend Vect operator-(Vect& lhs, Vect& rhs);
	friend Vect operator+(Vect& lhs, Vect& rhs);

	Vect& operator-=(Vect& rhs);
	Vect& operator*=(Vect& rhs);
	Vect& operator+=(Vect& rhs);

	bool operator==(Vect& rhs);
	std::vector<int> give_vect();
	void print();

	//~~~~~~~~~~CONST~~~~~~~~~~~~~~

	ConstVectItr begin() const;// { return VectItr(*this, 0); }
	ConstVectItr end() const;// { return VectItr(*this, int(vect.size())); }
	const int& at(int index) const;// { return vect.at(index); }
	const int& operator[](int index) const;
	int size() const { return vect.size(); }

	// some repetitive guys
	Vect operator*(int amt) const;
	Vect operator-(int amt) const;
	Vect operator+(int amt) const;
	friend Vect operator+(int amt, const Vect& rhs);
	friend Vect operator*(int amt, const Vect& rhs);
	friend Vect operator-(int amt, const Vect& rhs);

	// more repetitive guys
	friend Vect operator*(const Vect& lhs, Vect& rhs);
	friend Vect operator-(const Vect& lhs, Vect& rhs);
	friend Vect operator+(const Vect& lhs, Vect& rhs);
	friend Vect operator*(Vect& lhs, const Vect& rhs);
	friend Vect operator-(Vect& lhs, const Vect& rhs);
	friend Vect operator+(Vect& lhs, const Vect& rhs);
	friend Vect operator*(const Vect& lhs, const Vect& rhs);
	friend Vect operator-(const Vect& lhs, const Vect& rhs);
	friend Vect operator+(const Vect& lhs, const Vect& rhs);
	Vect& operator-=(const Vect& rhs);
	Vect& operator*=(const Vect& rhs);
	Vect& operator+=(const Vect& rhs);

	bool operator==(Vect& rhs) const;
	std::vector<int> give_vect() const;
	void print() const;
};

//--------------------- ConstVectItr Class ---------------------------
class ConstVectItr {
protected:
	const Vect* over;
	int pos;
public:
	ConstVectItr(const Vect& v) : over(&v), pos(0) {}
	ConstVectItr(const Vect& v, int pos) : over(&v), pos(pos) {}
	ConstVectItr& operator++();
	ConstVectItr& operator++(int);
	const int& operator*();

	bool operator==(const ConstVectItr& rhs);
	bool operator!=(const ConstVectItr& rhs);
};

//--------------------- ConstVectItr Funcs ---------------------------

ConstVectItr& ConstVectItr::operator++() {
	pos++;
	return *this;
}
ConstVectItr& ConstVectItr::operator++(int) {
	ConstVectItr copy(*this);
	++(*this);
	return copy;
}

const int& ConstVectItr::operator*() { return over->at(pos); }

bool ConstVectItr::operator==(const ConstVectItr& rhs) {
	// if (static_cast<bool>(*this) and rhs) { //both are in bounds
	if (pos >= 0 and pos < over->size()) {
		if (over == rhs.over) {
			return pos == rhs.pos;
		}
		else {
			return false;
		}
	}
	else if ((pos < 0 or pos >= over->size()) && (rhs.pos < 0 or rhs.pos >= rhs.over->size())) { //both out of bounds
		return over == rhs.over; //must be iteratring over same object
	}
	else {
		return false;
	}
}
bool ConstVectItr::operator!=(const ConstVectItr& rhs) { return !(*this == rhs); }


//--------------------- VectItr Class ---------------------------
class VectItr {
protected:
	Vect* over;
	int pos;
public:
	VectItr(Vect& v) : over(&v), pos(0) {}
	VectItr(Vect& v, int pos) : over(&v), pos(pos) {}
	VectItr& operator++();
	VectItr& operator++(int);
	int& operator*();

	bool operator==(const VectItr& rhs);
	bool operator!=(const VectItr& rhs);
};

//--------------------- Matrix Class ---------------------------
class Matrix {
protected:
	// std::vector<std::vector<int>> mat;
	std::vector<Vect> mat;
public:
	static Matrix ident(int dim);
	Matrix(std::vector<std::vector<int>>& v);
	Matrix(int numrows, Vect& v);
	Matrix(int numrows, std::vector<int>& v);
	void print();
	Vect& rowAt(int row);
	Vect& at(int row);
	ColOnlyVect& colAt(int row);
	int size() { return mat.size(); }
	MatrixRowItr begin();// { return VectItr(*this, 0); }
	MatrixRowItr rowBegin();
	MatrixRowItr rowEnd();
	MatrixRowItr end();
	int getNumRows();
	int getNumCols();
	Vect& operator[](int row);
	int& at(int row, int col);
	void push_back(Vect& m);
	Matrix& operator-();

	Matrix operator*(int value);
	Matrix& operator*=(int value);

	Matrix operator+(Matrix* );

};
int Matrix::getNumRows() {
	return mat.size();
}
int Matrix::getNumCols() {
	if (mat.size() == 0) return 0;
	return mat.at(0).size();
}

//--------------------- MatrixRowItr Class ---------------------------
class MatrixRowItr {
protected:
	Matrix* over;
	int row;
public:
	MatrixRowItr(Matrix& v) : over(&v), row(0) {}
	MatrixRowItr(Matrix& v, int row) : over(&v), row(row) {}
	MatrixRowItr& operator++();
	MatrixRowItr& operator++(int);
	Vect& operator*();

	bool operator==(const MatrixRowItr& rhs);
	bool operator!=(const MatrixRowItr& rhs);
};

//--------------------- ColOnlyVect Class ---------------------------
class ColOnlyVect {
protected:
	std::vector<int*> colvect;
public:
	ColOnlyVect(std::vector<int*>& thi) {
		for (int i = 0; i < thi.size(); i++) {
			colvect.push_back(&*(thi.at(i)));
		}
	}
	ColOnlyVect() { colvect.clear(); }
	void push_back(int& j) { colvect.push_back(&j); }


	ColOnlyVectItr begin();// { return ColOnlyVectItr(*this, 0); }
	ColOnlyVectItr end();// { return ColOnlyVectItr(*this, int(ColOnlyVect.size())); }
	int& at(int index);// { return ColOnlyVect.at(index); }
	int size() { return colvect.size(); }
	ColOnlyVect& make_reference_ColOnlyVect() { return (*this); }
	ColOnlyVect& operator+=(int amt);
	bool operator==(ColOnlyVect& rhs);
	std::vector<int> give_ColOnlyVect();
	void print();
};

//--------------------- ColOnlyVectItr Class ---------------------------
class ColOnlyVectItr {
protected:
	ColOnlyVect* over;
	int pos;
public:
	ColOnlyVectItr(ColOnlyVect& v) : over(&v), pos(0) {}
	ColOnlyVectItr(ColOnlyVect& v, int pos) : over(&v), pos(pos) {}
	ColOnlyVectItr& operator++();
	ColOnlyVectItr& operator++(int);
	int& operator*();

	bool operator==(const ColOnlyVectItr& rhs);
	bool operator!=(const ColOnlyVectItr& rhs);
};

//--------------------- MatrixRowItr Funcs ---------------------------

MatrixRowItr& MatrixRowItr::operator++() {
	row++;
	return *this;
}
MatrixRowItr& MatrixRowItr::operator++(int) {
	MatrixRowItr copy(*this);
	++(*this);
	return copy;
}

Vect& MatrixRowItr::operator*() { return over->rowAt(row); }

bool MatrixRowItr::operator==(const MatrixRowItr& rhs) {
	// if (static_cast<bool>(*this) and rhs) { //both are in bounds
	if (row >= 0 and row < over->size()) {
		if (over == rhs.over) {
			return row == rhs.row;
		}
		else {
			return false;
		}
	}
	else if ((row < 0 or row >= over->size()) && (rhs.row < 0 or rhs.row >= rhs.over->size())) { //both out of bounds
		return over == rhs.over; //must be iteratring over same object
	}
	else {
		return false;
	}
}
bool MatrixRowItr::operator!=(const MatrixRowItr& rhs) { return !(*this == rhs); }

//--------------------- VectItr Funcs ---------------------------

VectItr& VectItr::operator++() {
	pos++;
	return *this;
}
VectItr& VectItr::operator++(int) {
	VectItr copy(*this);
	++(*this);
	return copy;
}

int& VectItr::operator*() { return over->at(pos); }

bool VectItr::operator==(const VectItr& rhs) {
	// if (static_cast<bool>(*this) and rhs) { //both are in bounds
	if (pos >= 0 and pos < over->size()) {
		if (over == rhs.over) {
			return pos == rhs.pos;
		}
		else {
			return false;
		}
	}
	else if ((pos < 0 or pos >= over->size()) && (rhs.pos < 0 or rhs.pos >= rhs.over->size())) { //both out of bounds
		return over == rhs.over; //must be iteratring over same object
	}
	else {
		return false;
	}
}
bool VectItr::operator!=(const VectItr& rhs) { return !(*this == rhs); }



//--------------------- Matrix Class Funcs ---------------------------



Matrix Matrix::ident(int dim) {
	std::vector<int>p(dim, 0);
	Matrix matt(dim, p);
	int j = 0;
	for (int i = 0; i < dim; i++) {
		//matt.push_back(*(new Vect(dim, 0)));
		for (int j = 0; j < dim; j++) {
			matt.at(i).at(j) = 0;
			if (i == j) matt.at(i).at(j) = 1;
		}
	}
	return(matt);
}
Matrix::Matrix(int numrows, std::vector<int>& v) {
	mat.clear();
	for (int i = 0; i < numrows; i++) {
		mat.push_back(*(new Vect(v)));
	}
}
Matrix::Matrix(std::vector<std::vector<int>>& v) {
	for (int i = 0; i < v.size(); i++) {
		mat.push_back(*(new Vect(v.at(i))));
	}
}
Matrix::Matrix(int numrows, Vect& v) {
	for (int i = 0; i < numrows;i++)
		mat.push_back(v);
	// mat.push_back(v);
}
void Matrix::print() {
	std::cout << "\n";
	for (auto& re : mat) {
		for (auto& ref : re) {
			std::cout << ref << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
Vect& Matrix::rowAt(int row) { return mat.at(row); }
Vect& Matrix::at(int row) { return mat.at(row); }

// FIXME
ColOnlyVect& Matrix::colAt(int col) {
	ColOnlyVect* p = new ColOnlyVect();
	for (int i = 0; i < mat.size(); i++)
		(*p).push_back(mat.at(i).at(col));
	return *p;
}

MatrixRowItr Matrix::begin() { return MatrixRowItr(*this, 0); }
MatrixRowItr Matrix::rowBegin() { return MatrixRowItr(*this, 0); }
MatrixRowItr Matrix::rowEnd() { return MatrixRowItr(*this, int((this)->size())); }
MatrixRowItr Matrix::end() { return MatrixRowItr(*this, int((this)->size())); }
Vect& Matrix::operator[](int row) { return mat.at(row); }
int& Matrix::at(int row, int col) { return mat.at(row).at(col); }
void Matrix::push_back(Vect& m) { mat.push_back(m); }
Matrix& Matrix::operator-() {
	for (auto& ref : (*this)) {
		ref *= (-1);
	}
	return (*this);
}

Matrix& Matrix::operator*=(int value) {
	for (auto& ref : (*this)) {
		ref *= value;
	}
	return (*this);
}


Matrix Matrix::operator*(int value) {
	Matrix copy(*this);
	for (auto& ref : copy) {
		ref *= value;
	}
	return copy;
}


//--------------------- Vect Class Funcs ---------------------------

VectItr Vect::begin() { return VectItr(*this, 0); }
VectItr Vect::end() { return VectItr(*this, int(vect.size())); }
int& Vect::at(int index) { return vect.at(index); }
int& Vect::operator[](int index) { return vect.at(index); }
Vect& Vect::operator+=(int amt) {
	for (auto& ref : vect) {
		ref += amt;
	}
	return (*this);
}
Vect& Vect::operator-=(int amt) {
	for (auto& ref : vect) {
		ref -= amt;
	}
	return (*this);
}
//Vect& Vect::operator*(int lhs, Vect& rhs) {
//	Vect newV(*this);
//	for (auto& ref : newV) {
//		ref *= amt;
//	}
//	return newV;
//}
Vect& Vect::operator*=(int amt) {
	for (auto& ref : vect) {
		ref *= amt;
	}
	return (*this);
}
Vect& Vect::operator-() {
	for (auto& ref : vect) {
		ref *= (-1);
	}
	return (*this);
}

Vect& Vect::operator=(Vect& rhs) {
	int i = 0;
	vect.clear();
	for (auto& ref : rhs) {
		vect.push_back(ref);
	}
	return (*this);
	//auto rhs_itr = rhs.begin();
	//auto my_itr = (*this).begin();
	//for (;rhs_itr != rhs.end() and my_itr != (*this).end(); rhs_itr++, my_itr++) {
	//	
	//}
}
Vect Vect::operator*(int amt) {
	Vect newV(*this);
	for (int i = 0; i < (*this).size(); i++)
		newV.at(i) *= amt;
	return newV;
}
Vect Vect::operator-(int amt) {
	Vect newV(*this);
	for (int i = 0; i < (*this).size(); i++)
		newV.at(i) -= amt;
	return newV;
}
Vect Vect::operator+(int amt) {
	Vect newV(*this);
	for (int i = 0; i < (*this).size(); i++)
		newV.at(i) += amt;
	return newV;
}
//Vect Vect::operator+(int amt, Vect& rhs) {
//	Vect newV(rhs);
//	for (int i = 0; i < (*this).size(); i++)
//		newV.at(i) += amt;
//	return newV;
//}
Vect operator+(int amt, Vect& rhs) { return rhs + amt; }
Vect operator*(int amt, Vect& rhs) { return rhs * amt; }
Vect operator-(int amt, Vect& rhs) { return -rhs + amt; }
Vect operator*(Vect& lhs, Vect& rhs) {
	Vect newV(lhs);
	newV *= rhs;
	return (newV);
}
Vect operator-(Vect& lhs, Vect& rhs) {
	Vect newV(lhs);
	newV -= rhs;
	return (newV);
}
Vect operator+(Vect& lhs, Vect& rhs) {
	Vect newV(lhs);
	newV += rhs;
	return (newV);
}
Vect& Vect::operator+=(Vect& rhs) {
	int i = 0;
	for (auto& ref : (*this)) {
		ref += rhs.at(i); i++;
	}
	return (*this);
}
Vect& Vect::operator-=(Vect& rhs) {
	int i = 0;
	for (auto& ref : (*this)) {
		ref -= rhs.at(i); i++;
	}
	return (*this);
}
Vect& Vect::operator*=(Vect& rhs) {
	int i = 0; int val = 0;
	for (auto& ref : (*this)) {
		val += ref * rhs.at(i);
		i++;
	}
	// std::vector<int> ans({ val });
	vect.clear();
	vect.push_back(val);
	return (*this);
}

bool Vect::operator==(Vect& rhs) {
	if (rhs.size() != vect.size()) return false;
	for (int i = 0; i < rhs.size(); i++) {
		if (vect.at(i) != rhs.at(i))
			return false;
	}
	return true;
}
std::vector<int> Vect::give_vect() {
	std::vector<int> copy;
	for (auto& ref : vect) {
		copy.push_back(ref);
	}
	return copy;
}
void Vect::print() { std::cout << "\n";
	for (int i = 0; i < vect.size(); i++) std::cout << vect.at(i) << " ";
	std::cout << "\n";
}



//~~~~~~~~~~~CONST~~~~~~~~~~~~~~~~


ConstVectItr Vect::begin() const { return ConstVectItr(*this, 0); }
ConstVectItr Vect::end() const { return ConstVectItr(*this, int(vect.size())); }
const int& Vect::at(int index) const { return (vect.at(index)); }
const int& Vect::operator[](int index) const { return (vect.at(index)); }

Vect operator+(int amt, const Vect& rhs) { return rhs + amt; }
Vect operator*(int amt, const Vect& rhs) { return rhs * amt; }
Vect operator-(int amt, const Vect& rhs) {
	Vect midV(rhs);
	return -midV + amt;
}
Vect Vect::operator*(int amt) const {
	Vect newV(*this);
	for (auto& ref : newV) ref *= amt;
	return newV;
}
Vect Vect::operator-(int amt) const {
	Vect newV(*this);
	for (auto& ref : newV) ref -= amt;
	return newV;
}
Vect Vect::operator+(int amt) const {
	Vect newV(*this);
	for (auto& ref : newV) ref += amt;
	return newV;
}
bool Vect::operator==(Vect& rhs) const {
	Vect newV(*this);
	return (newV == rhs);
}
std::vector<int> Vect::give_vect() const {
	std::vector<int> copy;
	for (auto& ref : vect) {
		copy.push_back(ref);
	}
	return copy;
}
void Vect::print() const {
	std::cout << "\n";
	for (int i = 0; i < vect.size(); i++) std::cout << vect.at(i) << " ";
	std::cout << "\n";
}

//~~~
Vect operator*(const Vect& lhs, Vect& rhs) {
	Vect midV1(lhs);
	Vect midV2(rhs);
	midV1 *= midV2;
	return midV1;
}
Vect operator-(const Vect& lhs, Vect& rhs) {
	Vect midV1(lhs);
	Vect midV2(rhs);
	midV1 -= midV2;
	return midV1;
}
Vect operator+(const Vect& lhs, Vect& rhs) {
	Vect midV1(lhs);
	Vect midV2(rhs);
	midV1 += midV2;
	return midV1;
}
Vect operator*(Vect& lhs, const Vect& rhs) {
	Vect midV1(lhs);
	Vect midV2(rhs);
	midV1 *= midV2;
	return midV1;
}
Vect operator-(Vect& lhs, const Vect& rhs) {
	Vect midV1(lhs);
	Vect midV2(rhs);
	midV1-= midV2;
	return midV1;
}
Vect operator+(Vect& lhs, const Vect& rhs) {
	Vect midV1(lhs);
	Vect midV2(rhs);
	midV1 += midV2;
	return midV1;
}
Vect operator*(const Vect& lhs, const Vect& rhs) {
	Vect midV1(lhs);
	Vect midV2(rhs);
	midV1 *= midV2;
	return midV1;
}
Vect operator-(const Vect& lhs, const Vect& rhs) {
	Vect midV1(lhs);
	Vect midV2(rhs);
	midV1 -= midV2;
	return midV1;
}
Vect operator+(const Vect& lhs, const Vect& rhs) {
	Vect midV1(lhs);
	Vect midV2(rhs);
	midV1 += midV2;
	return midV1;
}
Vect& Vect::operator-=(const Vect& rhs) {
	Vect midV(rhs);
	(*this) -= midV;
	return (*this);
}
Vect& Vect::operator*=(const Vect& rhs) {
	Vect midV(rhs);
	(*this) *= midV;
	return (*this);
}
Vect& Vect::operator+=(const Vect& rhs) {
	Vect midV(rhs);
	(*this) += midV;
	return (*this);
}
//~~~


//--------------------- ColOnlyVectItr Funcs ---------------------------

ColOnlyVectItr& ColOnlyVectItr::operator++() {
	pos++;
	return *this;
}
ColOnlyVectItr& ColOnlyVectItr::operator++(int) {
	ColOnlyVectItr copy(*this);
	++(*this);
	return copy;
}

int& ColOnlyVectItr::operator*() { return (over->at(pos)); }

bool ColOnlyVectItr::operator==(const ColOnlyVectItr& rhs) {
	// if (static_cast<bool>(*this) and rhs) { //both are in bounds
	if (pos >= 0 and pos < over->size()) {
		if (over == rhs.over) {
			return pos == rhs.pos;
		}
		else {
			return false;
		}
	}
	else if ((pos < 0 or pos >= over->size()) && (rhs.pos < 0 or rhs.pos >= rhs.over->size())) { //both out of bounds
		return over == rhs.over; //must be iteratring over same object
	}
	else {
		return false;
	}
}
bool ColOnlyVectItr::operator!=(const ColOnlyVectItr& rhs) { return !(*this == rhs); }

//--------------------- ColOnlyVect Class Funcs ---------------------------

ColOnlyVectItr ColOnlyVect::begin() { return ColOnlyVectItr(*this, 0); }
ColOnlyVectItr ColOnlyVect::end() { return ColOnlyVectItr(*this, int(colvect.size())); }
int& ColOnlyVect::at(int index) { return *(colvect.at(index)); }
ColOnlyVect& ColOnlyVect::operator+=(int amt) {
	for (auto& ref : colvect) {
		*ref += amt;
	}
	return (*this);
}
bool ColOnlyVect::operator==(ColOnlyVect& rhs) {
	if (rhs.size() != colvect.size()) return false;
	for (int i = 0; i < rhs.size(); i++) {
		if (*(colvect.at(i)) != (rhs.at(i)))
			return false;
	}
	return true;
}
std::vector<int> ColOnlyVect::give_ColOnlyVect() {		// return a copy
	std::vector<int> copy;
	for (auto& ref : colvect) {
		copy.push_back(*ref);
	}
	return copy;
}
void ColOnlyVect::print() {
	std::cout << "\n";
	for (int i = 0; i < colvect.size(); i++) std::cout << *(colvect.at(i)) << " ";
	std::cout << "\n";
}


//--------------------- Driver Code ---------------------------

int main() {

	// matrix initialization strategies
	std::vector<int>vec = { 1,2,3,4,5 };
	Vect joe(vec);

	Matrix mat(5, joe);
	mat.print();

	mat.rowAt(0) += 32;
	mat.rowAt(0).print();

	// matrix initialization strategy: setting matrix equal to 2D vector
	std::vector<std::vector<int>>v2 = { {1,2},{3,4},{5,6} };
	Matrix mat2(v2);
	mat2.print();

	Matrix mat3(v2);
	std::cout << "THIS";
	for (auto& ref : mat3) {
		for (const auto& reff : ref)
			std::cout << reff << " ";
		std::cout << "\n";
	}

	//// modifying matrix rows
	//for (auto& ref : mat3.rowAt(0)) {
	//	ref += 2;
	//}
	//for (auto& ref : mat3.rowAt(0)) {
	//	ref += 1;
	//}
	mat3.print();

	//// TODO: fix this colAt func
	//for (auto& ref : mat3.colAt(0)) {
	//	ref += 2;
	//}
	Vect a = mat3.rowAt(1);
	Vect b = mat3.rowAt(1);

	//Vect c = mat3.colAt(3);
	
	a.print(); b.print();
	//Vect c = a - 2;
	//(a-2).print();

	//Vect d = a + b;
	//d += 32;
	//d.print();	

	//mat3.print();
	//mat3.rowAt(0) += 23;
	//mat3.print();
	//mat3.rowAt(1) *= mat3.rowAt(2);
	//mat3.print();
	
	//mat3.at(0, 0) -= 99;
	//mat3[0] += 32;
	//mat3.colAt(0).print();
	//mat3.print();
	//mat3.at(0).at(0) = 99;
	//for (auto itr = mat3.rowBegin(); itr != mat3.rowEnd(); itr++) {
	//	(*itr).print();
	//}
	//for (auto& ref : mat3)
	//	ref.print();
	mat3[0][0] -= 32;
	mat3[0] += 9999;
	mat3.print();
	Matrix j = Matrix::ident(5);
	j.print();

	//// initilize vector of Vect class
	//std::vector<std::vector<int>>ans{ {10, 20},
	//			{30, 40},
	//			{45, 50},
	//			{100, 200} };
	//std::vector<Vect> initializer(ans.begin(), ans.end());
	//for (auto& ref : initializer) ref.print();

	a[1] += 32;
	a.print();

	//// test case: vector of vector refs
	std::vector<std::vector<int>> ans{ {10, 20},
				{30, 40},
				{45, 50},
				{100, 200} };
	std::vector<Vect> vectors(ans.begin(), ans.end());
	std::vector<VectItr> initializer(vectors.begin(), vectors.end());


	// mat3.print();

	//// FIXME
	//mat3.colAt(0) += 99999;
	//mat3.print();
	
	mat3.print();
	Matrix mat4= -mat3;
	mat4.print();

	mat3 *= 999;
	mat3 *= 999;
	Matrix d = mat3 * 3;

	Matrix f = mat3 + mat3;


	return 0;
}
