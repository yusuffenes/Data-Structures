#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct node
{
    int data;
    int height;
    node* left;
    node* right;
};

node* root = nullptr;

int height(node* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {
        return node->height;
    }
}
int dengeleme(node* node) 
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {
        return height(node->left) - height(node->right);
    }
}
void yeniHeight(node* node) 
{
    if (node != nullptr)
    {
        node->height = 1 + max(height(node->left), height(node->right));
    }
}
node* sagaKaydir(node* kok)
{
    node* yeniKok = kok->left;
    node* altAgac = yeniKok->right;

    yeniKok->right = kok;
    kok->left = altAgac;

    yeniHeight(yeniKok);
    yeniHeight(kok);

    return yeniKok;
}
node* solaKaydir(node * kok) 
{
    node* yeniKok = kok->right;
    node* altAgac = yeniKok->left;

    yeniKok->left = kok;
    kok->right = altAgac;

    yeniHeight(kok);
    yeniHeight(yeniKok);

    return yeniKok;
}

node* yeniOlustur(int key) 
{
    node* temp = new node();
    temp->data = key;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->height = 1;

    if (root ==nullptr)
    {
        root = temp;
    }
    return temp;

}

node* ekle(node* node,int key)
{
    if (node == nullptr)
    {
        return yeniOlustur(key);
    }
    if (key<node->data)
    {
        node->left = ekle(node->left, key);
    }
    else if (key>node->data)
    {
        node->right = ekle(node->right, key);
    }
    else
    {
        return node;
    }
    yeniHeight(node);

    int denge = dengeleme(node);
    if (denge > 1 && key < node->left->data) {
        return sagaKaydir(node);
    }

    
    if (denge < -1 && key > node->right->data) {
        return solaKaydir(node);
    }

    
    if (denge > 1 && key > node->left->data) {
        node->left = solaKaydir(node->left);
        return sagaKaydir(node);
    }

    
    if (denge < -1 && key < node->right->data) {
        node->right = sagaKaydir(node->right);
        return solaKaydir(node);
    }

    return node;
    
};
void inOrder(node* root) {
    if (root != nullptr)
    {
        inOrder(root->left);
        cout << root->data<<" - ";
        inOrder(root->right);
    }
}
void preOrder(node* root) {
    if (root != nullptr)
    {
        cout << root->data <<" - ";
        inOrder(root->left);
        inOrder(root->right);
    }
}
void postOrder(node* root) {
    if (root != nullptr)
    {
        
        inOrder(root->left);
        inOrder(root->right);
        cout << root->data << " - ";
    }
}
int dugumSayisi(node* current) {
    if (current == nullptr) {
        return 0;
    }
    return 1 + dugumSayisi(current->left) + dugumSayisi(current->right);
}
node* ara(int arananDeger)
{
    node* current;
    current = root;
    while (current != nullptr&&current->data != arananDeger)
    {
        if (current != nullptr)
        {
            cout << current->data;
            if (arananDeger < current->data)
            {
                current = current->left;
            }
            if (arananDeger > current->data)
            {
                current = current->right;
            }
        }
        if (current == nullptr)
        {
            cout << "\n aradigini sayi agacta bulunmuyor!!!...";
            return nullptr;
        }

    }
    cout << current->data;
    return current;
}

int agacYuksekligi(node* current) {
    if (current == nullptr) {
        return 0;
    }
    int leftHeight = agacYuksekligi(current->left);
    int rightHeight = agacYuksekligi(current->right);
    return 1 + max(leftHeight, rightHeight);
}


void agacTemizle(node*& current) {
    if (current != nullptr) {
        agacTemizle(current->left);
        agacTemizle(current->right);
        delete current;
        current = nullptr;
    }
}
node* enKucukDeger(node* current)
{
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}
node* silme(node* current, int key) {
    if (current == nullptr) {
        return current;
    }

    if (key < current->data) {
        current->left = silme(current->left, key);
    }
    else if (key > current->data) {
        current->right = silme(current->right, key);
    }
    else {
        if (current->left == nullptr) {
            node* temp = current->right;
            delete current;
            return temp;
        }
        else if (current->right == nullptr) {
            node* temp = current->left;
            delete current;
            return temp;
        }


        node* temp = enKucukDeger(current->right);
        current->data = temp->data;
        current->right = silme(current->right, temp->data);
    }

    return current;
}

void displayMenu() {
    cout << endl;
    cout << "----------------------------------------------------\n";
    cout << "                AVL Tree Uygulamasi\n";
    cout << "----------------------------------------------------\n";
    cout << "1 - Sayi Ekle\n";
    cout << "2 - Siralama Secenekleri\n";
    cout << "3 - Arama\n";
    cout << "4 - Silme\n";
    cout << "5 - Agac Yuksekligi\n";
    cout << "6 - En Kucuk Deger\n";
    cout << "7 - Dugum Sayisi\n";
    cout << "8 - Agaci Temizle\n";
    cout << "0 - Cikis\n";
    cout << "----------------------------------------------------\n";
}

int main()
{
    int secim;
    while (true)
    {
        displayMenu();
        cout << "Secim : ";
        cin >> secim;


        switch (secim)
        {
        default:
            cout << "Hatali secim! Lutfen gecerli bir secim yapin.\n";
            break;
        case 0:
            cout << "Programdan cikiliyor...\n";
            agacTemizle(root);
            return 0;
        case 1:
            int eklenecekSayi;
            cout << "Eklenecek Sayi: ";
            cin >> eklenecekSayi;
            ekle(root, eklenecekSayi);
            cout << "Sayi basariyla eklendi.\n";
            break;
        case 2:
            int siralamaSecim;
            cout << "1- InOrder\n";
            cout << "2- PreOrder\n";
            cout << "3- PostOrder\n";
            cout << "Siralama Secim: ";
            cin >> siralamaSecim;

            switch (siralamaSecim) {
            default:
                cout << "Hatali secim! Lutfen gecerli bir secim yapin.\n";
                break;
            case 1:
                cout << "InOrder Siralamasi:\n";
                inOrder(root);
                cout << endl;
                break;
            case 2:
                cout << "PreOrder Siralamasi:\n";
                preOrder(root);
                cout << endl;
                break;
            case 3:
                cout << "PostOrder Siralamasi:\n";
                postOrder(root);
                cout << endl;
                break;
            }
            break;
        case 3:
            int aramaDeger;
            cout << "Aramak istediginiz deger: ";
            cin >> aramaDeger;
            cout << endl;
            if (ara(aramaDeger) != nullptr) {
                cout << "Deger bulundu!\n";
            }
            else {
                cout << "Aranan deger agacta bulunmuyor.\n";
            }
            break;
        case 4:
            int silinecekDeger;
            cout << "Silinecek deger: ";
            cin >> silinecekDeger;
            root = silme(root, silinecekDeger);
            cout << "Deger basariyla silindi.\n";
            break;
        case 5:
            cout << "Agac Yuksekligi: " << height(root) << endl;
            break;
        case 6:
            cout << "En Kucuk Deger: " << enKucukDeger(root)->data << endl;
            break;
        case 7:
            cout << "Dugum Sayisi: " << dugumSayisi(root) << endl;
            break;
        case 8:
            agacTemizle(root);
            cout << "Agac temizlendi.\n";
            break;
        
        }
    }
}

