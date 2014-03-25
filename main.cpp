#include <iostream>
#include <cstdio>

using namespace std;

template <typename T>
class Elem{ //węzeł
private:
  T value; //wartość elementu
  Elem<T>* next_e; //następny element
  Elem<T>* prev_e; //poprzedni element
public:
  Elem(){next_e=prev_e=NULL;} //konstruktor
  T RetVal(){return value;}  //zwraca wartosc obiektu
  /**
   * Zmienia wartosc value obiektu.
   */
  void SetVal(const T &NewVal){value=NewVal;}
  /**
   * Zwraca wskaznik na nastepny element.
   */
  Elem<T>* RetNext(){return next_e;}
  /**
   * Zwraca wskaznik na poprzedni element.
   */
  Elem<T>* RetPrev(){return prev_e;}
  /**
   * Zmienia wartosc wskaznika next_e.
   */
  void SetNext(Elem* NewNextEl){next_e=NewNextEl;}
  /**
   * Zmienia wartosc wskaznika prev_e.
   */
  void SetPrev(Elem* NewPrevEl){prev_e=NewPrevEl;}
  /**
   * Sprawdza czy wezel jest rozlaczony.
   */
  bool czyRozlaczony() const { return ((next_e==NULL)&&(prev_e==NULL));}
};


template <typename T>
class Deque {
public:
  /**
   * konstruktor
   */
  Deque()
  {head = tail = NULL;
    Rozmiar=0;
  }
  /**
   * konstruktor kopiujacy
   */
  Deque(Deque &D)
  {
    head=D.head;
    tail=D.tail;
    Rozmiar=D.Rozmiar;
  }
  /**
   * destruktor
   */
  ~Deque() 
  {
    delete head;
    delete tail;
  }
  /**
   * Zwraca ilość obiektów przechowywanych w deque.
   */
  int rozmiar() const {return Rozmiar;}
  /**
   * Zwraca wskaznik na head.
   */
  Elem<T>* RetHead(){return head;}
  /**
   * Zwraca wskaznik na tail.
   */
  Elem<T>* RetTail(){return tail;}
  /**
   * Zwieksza zmienna Rozmiar o wartosc val.
   */
  void zwiekszRozmiar(const int val){Rozmiar=Rozmiar+val;}
  /**
   * Zmniejsza zmienna Rozmiar o wartosc val.
   */
  void zmniejszRozmiar(const int val){Rozmiar=Rozmiar-val;}
  /**
   * Zwraca true jeśli deque jest pusty.
   */
  bool isEmpty() const { return ((head==NULL)&&(tail==NULL));}
  /**
   * Sprawdza czy wezel jest prawidlowo podlaczony.
   */
  bool czyPodlaczony(Elem<T> & El)
  {
    if(!isEmpty()&&rozmiar()!=0){
      Elem<T>* headsave=head;
      Elem<T>* tailsave=tail;
      while(headsave){
	if(&headsave!=&El){
	  headsave=headsave->RetNext();}
	else { 
	  if(&tailsave!=&El){
	    tailsave=tailsave->RetPrev();
	  }
	  else {
	    if(tailsave==headsave) return true;
	  }
	}
      }
      return false;
    }
    else  {string wyjatek="dequeue empty exception"; throw wyjatek;}
  }
  /**
   * Zwraca pierwszy obiekt w deque.
   * Wyrzuca DequeEmptyException jeśli deque jest pusty.
   */
  T pierwszy()
  {
    if(head!=NULL)
      return head->RetVal();
    else {string wyjatek="dequeue empty exception"; throw wyjatek;}
  }
  /**
   * Zwraca ostatni obiekt w deque.
   * Wyrzuca DequeEmptyException jeśli deque jest pusty
   */
  T ostatni()
  {
    if(tail!=NULL)
      return tail->RetVal();
    else  {string wyjatek="dequeue empty exception"; throw wyjatek;}
  }
  /**
   * Dodaje obiekt do poczatku deque’a.
   */
  void wstawPierwszy(const T& e)
  {
    Elem<T> *NewHead=new Elem<T>;
    NewHead->SetVal(e);
    if(isEmpty())
      head=tail=NewHead;
    else{
      NewHead->SetNext(head);
      head->SetPrev(NewHead);
      head=NewHead;
      delete NewHead;
    }
    zwiekszRozmiar(1);
  }
  /**
   * Kopiuje pierwszy obiekt deque’a.
   */
  void kopiujPierwszy()
  {
    Elem<T> e;
    Elem<T> *NewHead=new Elem<T>;
    e=head->RetVal();
    NewHead->SetVal(e);
    if(isEmpty())
      head=tail=NewHead;
    else{
      NewHead->SetNext(head);
      head->SetPrev(NewHead);
      head=NewHead;
      delete NewHead;
    }
    zwiekszRozmiar(1);
  }
  /**
   * Usuwa pierwszy obiekt z deque.
   * Wyrzuca DequeEmptyException jeśli deque jest pusty
   */
  void usunPierwszy()
  {
    if(head!=NULL){
      Elem<T>* MemSave;
      if(head==tail){
        MemSave=head;
        head=tail=NULL;
        delete MemSave;
        Rozmiar=0;}
      else{
        MemSave=head->RetNext();
        delete head;
        zmniejszRozmiar(1);
        head=MemSave;
        head->SetPrev(NULL);
      }
    }
    else  {string wyjatek="dequeue empty exception"; throw wyjatek;}
  }
  /**
   * Dodaje obiekt na końcu deque’a.
   */
  void wstawOstatni(const T& e)
  {
    Elem<T>* NewTail=new Elem<T>;
    NewTail->SetVal(e);
    NewTail->SetNext(NULL);
    if(isEmpty()){
      head=tail=NewTail;
      NewTail->SetPrev(NULL);}
    else{
      NewTail->SetPrev(tail);
      tail->SetNext(NewTail);
      tail=NewTail;
      delete NewTail;
    }
    zwiekszRozmiar(1);
  }
  /**
   * Kopiuje ostatni obiekt deque’a.
   */
  void kopiujOstatni()
  {
    Elem<T> e;
    Elem<T>* NewTail=new Elem<T>;
    e=tail->RetVal();
    NewTail->SetVal(e);
    NewTail->SetNext(NULL);
    if(isEmpty()){
      head=tail=NewTail;
      NewTail->SetPrev(NULL);}
    else{
      NewTail->SetPrev(tail);
      tail->SetNext(NewTail);
      tail=NewTail;
      delete NewTail;
    }
    zwiekszRozmiar(1);
  }
  /**
   * Usuwa ostatni obiekt z deque.
   * Wyrzuca DequeEmptyException jeśli deque jest pusty
   */
  void usunOstatni()
  {
    if(!isEmpty()){
      Elem<T>* MemSave;
      if(head==tail){
        MemSave=head;
        head=tail=NULL;
        delete MemSave;
        Rozmiar=0;}
      else{
	Elem<T>* MemSave;
	MemSave=tail->RetPrev();
	delete tail;
	zmniejszRozmiar(1);
	MemSave->SetNext(NULL);
	tail=MemSave;
	delete MemSave;
      }
    }
    else  {string wyjatek="dequeue empty exception"; throw wyjatek;}
  }
  /**
   * Odlacza od listy wezel wskazany przez iterator.
   */
  Elem<T> odlaczWezel(Elem<T> & El)
  {
    if(!isEmpty()&&rozmiar()!=0){
      Elem<T>* headsave=head;
      Elem<T>* saveprev, savenext;
      while(headsave){
	if(&headsave!=&El){
	  headsave=headsave->RetNext();}
        else {
	  saveprev=headsave->RetPrev();
	  savenext=headsave->RetNext();

	  saveprev->RetNext(savenext);
	  savenext->RetPrev(saveprev);
	  return headsave;
	}
      }
      cerr << "Brak wezla w liscie" << endl;
      return 0;	
    }
    else  {string wyjatek="dequeue empty exception"; throw wyjatek;}
  }
  /**
   * Dolacza do listy wezel El1 wskazany przez iterator przed wezel El2 podany w argumencie.
   */
  void dolaczWezel(Elem<T> & El1, Elem<T> & El2)
  {
    if(!isEmpty()&&rozmiar()!=0){
      Elem<T>* headsave=head;     
      while(headsave){
	if(&headsave!=&El2->RetPrev()){
	  headsave=headsave->RetNext();}
        else {
	  headsave->RetNext(El1);
	  El1->RetNext(El2);
	  El1->RetPrev(headsave);
	  El2->RetPrev(El1);              
	}
      }
      cerr << "Brak wezla w liscie" << endl;
      return 0;	
    }
    else  {string wyjatek="dequeue empty exception"; throw wyjatek;}
  }
  /**
   * Porownanie miedzy wskaznikami czy wskazuja na ten sam element.
   */
  bool porownajWskazniki(Elem<T> * ws1, Elem<T> * ws2)
  {
    if(ws1->RetNext()==ws2->RetNext()){
      if(ws1->RetPrev()==ws2->RetPrev()){
	if(ws1->RetVal()==ws2->RetVal()){
	  return true;
	}
      }
    }
    return false;
  }
  /**
   * Usuwa wszystkie obiekty z deque.
   * Wyrzuca DequeEmptyException jeśli deque jest pusty
   */
  void PopAll()
  {
    if(!isEmpty()){
      Elem<T>* MemSave;
      while(head){
	MemSave=head->RetNext();
	delete head;
	zmniejszRozmiar(1);
	head=MemSave;
      }
      head=tail=NULL;
    }
    else  {string wyjatek="dequeue empty exception"; throw wyjatek;}
  }
  /**
   * Wypisuje wszystkie obiekty z deque.
   * Wyrzuca deque empty exception jeśli deque jest pusty
   */
  void Printl()
  {
    if(!isEmpty()&&rozmiar()!=0){
      Elem<T>* headsave=head;
      while(head){
	cout << head->RetVal() << " ";
	head=head->RetNext();
      }
      cout << endl;
      head=headsave;
    }
    else  {string wyjatek="dequeue empty exception"; throw wyjatek;}
  }

  /*! 
   * \brief Przeciazenie operatora wyswietlajacego tablice <<.
   */
  friend ostream & operator << <> ( ostream &, Deque<T> & D );

  /*! 
   * \brief Przeciazenie operatora wczytujacego tablice >>.
   */
  friend istream & operator >> <> ( istream &, Deque<T> & D );

private:
  Elem<T>* head; //początek deque
  Elem<T>* tail; //koniec deque
  int Rozmiar;  //ilosc elementow
};

template <typename T>
ostream & operator << (ostream & StrmWy, Deque<T> & D){
  int rozmiar=D.rozmiar();
  if(!D.isEmpty()&&rozmiar!=0){
    Elem<T>* headsave=D.head;
    while(D.head){
      StrmWy << D.head->RetVal() << " ";
      D.head=D.head->RetNext();
    }
    cout << endl;
    D.head=headsave;
  }
  else  {string wyjatek="dequeue empty exception"; throw wyjatek;}

  return StrmWy;
}

template <typename T>
istream & operator >> (istream & StrmWe, Deque<T> & D){
  Elem<T> wartosc;
  int ilosc;
  cout << "ile elementow chcesz dodac?" << endl;
  cout << "ilosc = ";
  cin >> ilosc;
  for(unsigned int i=0;i<ilosc;i++)
    {
      StrmWe>>wartosc;
      D.wstawOstatni(wartosc);
    }
  return StrmWe;
}



int main(){
  cout << endl;
  return 0;
}
