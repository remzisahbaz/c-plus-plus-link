#include <iostream>
#include <fstream>
#include <string>

// Node sınıfı tanımlaması
class Node {
public:
    int data;
    Node* next;
};

// Tek Yönlü Bağlı Liste sınıfı tanımlaması
class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    void ekle(int veri);
    void yazdir();
    void yerDegistir(int indeks1, int indeks2);
private:
    Node* bas;
};

LinkedList::LinkedList() {
    bas = nullptr;
}

LinkedList::~LinkedList() {
    Node* current = bas;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::ekle(int veri) {
    Node* yeniDugum = new Node();
    yeniDugum->data = veri;
    yeniDugum->next = nullptr;
    
    if (bas == nullptr) {
        bas = yeniDugum;
    } else {
        Node* current = bas;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = yeniDugum;
    }
}

void LinkedList::yazdir() {
    Node* current = bas;
    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "NULL" << std::endl;
}

void LinkedList::yerDegistir(int indeks1, int indeks2) {
    if (indeks1 == indeks2) {
        return;  // İndeksler aynı ise yer değiştirme işlemi yapılmaz
    }
    
    Node* current1 = bas;
    Node* prev1 = nullptr;
    for (int i = 0; i < indeks1 && current1 != nullptr; i++) {
        prev1 = current1;
        current1 = current1->next;
    }
    
    Node* current2 = bas;
    Node* prev2 = nullptr;
    for (int i = 0; i < indeks2 && current2 != nullptr; i++) {
        prev2 = current2;
        current2 = current2->next;
    }
    
    if (current1 == nullptr || current2 == nullptr) {
        return;  // İndeksler geçerli değil, işlem yapılmaz
    }
    
    if (prev1 != nullptr) {
        prev1->next = current2;
    } else {
        bas = current2;
    }
    
    if (prev2 != nullptr) {
        prev2->next = current1;
    } else {
        bas = current1;
    }
    
    Node* temp = current1->next;
    current1->next = current2->next;
    current2->next = temp;
}

int main() {
    // Dosya okuma işlemi
    std::ifstream dosya("data.txt");
    std::string satir;
    
    LinkedList yukariListeler[3]; // Yukarı yönlü listeler
    LinkedList asagiListeler[3];  // Aşağı yönlü listeler
    
    // Dosyayı satır satır okuyarak listelere verileri yerleştirme
    int satirIndex = 0;
    while (std::getline(dosya, satir)) {
        LinkedList yukariListe;  // Satır için yeni yukarı yönlü liste
        LinkedList asagiListe;   // Satır için yeni aşağı yönlü liste
        
        for (char c : satir) {
            if (isdigit(c)) {
                int rakam = c - '0';
                if (rakam % 10 == 0) {
                    yukariListe.ekle(rakam);
                } else {
                    asagiListe.ekle(rakam);
                }
            }
        }
        
        yukariListeler[satirIndex] = yukariListe;
        asagiListeler[satirIndex] = asagiListe;
        satirIndex++;
    }
    
    // Yukarı yönlü listeleri yazdırma
    for (int i = 0; i < 3; i++) {
        std::cout << "Yukari Yonlu Liste[" << i << "]: ";
        yukariListeler[i].yazdir();
    }
    
    // Aşağı yönlü listeleri yazdırma
    for (int i = 0; i < 3; i++) {
        std::cout << "Asagi Yonlu Liste[" << i << "]: ";
        asagiListeler[i].yazdir();
    }
    
    // Kullanıcıdan indeks konumlarını alalım
    int konumA, konumB;
    std::cout << "Konum A: ";
    std::cin >> konumA;
    std::cout << "Konum B: ";
    std::cin >> konumB;
    
    // Listeleri yer değiştirme işlemi
    yukariListeler[konumA].yerDegistir(konumA, konumB);
    asagiListeler[konumA].yerDegistir(konumA, konumB);
    
    std::cout << "\nYeni Olusan Listeler:\n";
    
    // Yukarı yönlü listeleri yazdırma
    for (int i = 0; i < 3; i++) {
        std::cout << "Yukari Yonlu Liste[" << i << "]: ";
        yukariListeler[i].yazdir();
    }
    
    // Aşağı yönlü listeleri yazdırma
    for (int i = 0; i < 3; i++) {
        std::cout << "Asagi Yonlu Liste[" << i << "]: ";
        asagiListeler[i].yazdir();
    }
    
    return 0;
}
