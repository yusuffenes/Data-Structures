#include <iostream>
#include <string>

using namespace std;

struct node {
  int data;
  node* next;
};

node* head = nullptr; // Bağlı listenin başlangıç düğümü

node* newNode(int key) {
  node* temp = new node();
  temp->data = key;
  temp->next = nullptr;
  return temp;
}

void insertAtBeginning(int key) {
  node* temp = newNode(key);
  temp->next = head;
  head = temp;
}


void insertAtEnd(int key) {
  node* temp = newNode(key);
  if (head == nullptr) {
    head = temp;
    return;
  }
  node* current = head;
  while (current->next != nullptr) {
    current = current->next;
  }
  current->next = temp;
}


void printList() {
  node* current = head;
  while (current != nullptr) {
    cout << current->data << " -> ";
    current = current->next;
  }
  cout << "nullptr" << endl;
}


bool search(int key) {
  node* current = head;
  while (current != nullptr) {
    if (current->data == key) {
      return true;
    }
    current = current->next;
  }
  return false;
}

void deleteNode(int key) {
  if (head == nullptr) {
    return;
  }
  node* temp = head;
  if (temp->data == key) {
    head = head->next;
    delete temp;
    return;
  }
  node* current = head;
  while (current->next != nullptr) {
    if (current->next->data == key) {
      break;
    }
    current = current->next;
  }
  if (current->next != nullptr) {
    node* temp = current->next;
    current->next = temp->next;
    delete temp;
  }
}

int getSize() {
  int count = 0;
  node* current = head;
  while (current != nullptr) {
    count++;
    current = current->next;
  }
  return count;
}


int main() {
  while (true) {
    cout << "\nBağlı Liste Menüsü:" << endl;
    cout << "1. Başa Ekle" << endl;
    cout << "2. Sona Ekle" << endl;
    cout << "3. Yazdır" << endl;
    cout << "4. Anahtar Ara" << endl;
    cout << "5. Düğüm Sil" << endl;
    cout << "6. Boyut" << endl;
    cout << "7. Çıkış" << endl;
    cout << "Seçiminizi girin: ";
    int secim;
    cin >> secim;

    switch (secim) {
      case 1:
        int eklenecekDeger;
        cout << "Başa eklenecek değeri girin: ";
        cin >> eklenecekDeger;
        insertAtBeginning(eklenecekDeger);
        break;
      case 2:
        cout << "Sona eklenecek değeri girin: ";
        cin >> eklenecekDeger;
        insertAtEnd(eklenecekDeger);
        break;
      case 3:
        printList();
        break;
      case 4:
        int anahtar;
        cout << "Aranacak anahtarı girin: ";
        cin >> anahtar;
        if (search(anahtar)) {
          cout << "Anahtar bulundu!" << endl;
        } else {
          cout << "Anahtar bulunamadı." << endl;
        }
        break;
      case 5:
        cout << "Silinecek düğümün anahtarını girin: ";
        cin >> anahtar;
        deleteNode(anahtar);
        break;
      case 6:
        cout << "Listenin boyutu: " << getSize() << endl;
        break;
      case 7:
        return 0;
      default:
        cout << "Hatalı seçim! Lütfen geçerli bir seçim yapın." << endl;
    }
  }
}
