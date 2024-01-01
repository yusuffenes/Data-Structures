#include <string>
#include <iostream>

using namespace std;


typedef struct node {
    int data;
    node* left;
    node* right;
}node;

node* root = nullptr;

node* newNode(int key) {
    node* temp = new node();
    temp->data = key;
    temp->left = nullptr;
    temp->right = nullptr;

    if (root == nullptr)
    {
        root = temp;
    }
    return temp;
}

void inOrder(node* current)    //LNR
{    
    if (current != nullptr)
    {
        inOrder(current->left);
        cout << current->data<<"  -  ";
        inOrder(current->right);
    }
}

void preOrder(node*current)    // NLR
{
    if (current !=nullptr)
    {
        cout << current->data << " - ";
        preOrder(current->left);
        preOrder(current->right);


    }
}

void postOrder(node* current)  //LRN
{
    if (current != nullptr)
    {
        postOrder(current->left);
        postOrder(current->right);
        cout << current->data << " - ";
    }
}

node *Ekle(node* node,int key) 
{
    if (node==nullptr)
    {
        return newNode(key);
    }
    if (key<node->data)
    {
        node->left = Ekle(node->left, key);
    }
    else if (key>node->data)
    {
        node->right = Ekle(node->right, key);
    }
    return node;

}

node* search(int searched) 
{
    node* current;
    current = root;
    while (current->data != searched)
    {
        if (current != nullptr)
        {
            cout << current->data;
            if (searched<current->data)
            {
                current = current->left;
            }
            if (searched>current->data)
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

node* enKucukDeger(node* current)
{
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

node* enBuyukDeger(node* current) {
    while (current->right != nullptr) {
        current = current->right;
    }
    return current;
}

node* deleteNode(node* current, int key) {
    if (current == nullptr) {
        return current;
    }

    if (key < current->data) {
        current->left = deleteNode(current->left, key);
    }
    else if (key > current->data) {
        current->right = deleteNode(current->right, key);
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
        current->right = deleteNode(current->right, temp->data);
    }

    return current;
}

void depthFirstTraversal(node* current, int targetDepth, int currentDepth = 0) {
    if (current != nullptr) {
        if (currentDepth == targetDepth) {
            cout << current->data << " - ";
        }
        depthFirstTraversal(current->left, targetDepth, currentDepth + 1);
        depthFirstTraversal(current->right, targetDepth, currentDepth + 1);
    }
}

int countNodes(node* current) {
    if (current == nullptr) {
        return 0;
    }
    return 1 + countNodes(current->left) + countNodes(current->right);
}

int countLeaves(node* current) {
    if (current == nullptr) {
        return 0;
    }
    if (current->left == nullptr && current->right == nullptr) {
        return 1;
    }
    return countLeaves(current->left) + countLeaves(current->right);
}

void clearTree(node*& current) {
    if (current != nullptr) {
        clearTree(current->left);
        clearTree(current->right);
        delete current;
        current = nullptr;
    }
}

int height(node* current) {
    if (current == nullptr) {
        return 0;
    }
    int leftHeight = height(current->left);
    int rightHeight = height(current->right);
    return 1 + max(leftHeight, rightHeight);
}

void findSmallerValues(node* current, int target) {
    if (current != nullptr) {
        if (current->data < target) {
            cout << current->data << " - ";
        }
        findSmallerValues(current->left, target);
        findSmallerValues(current->right, target);
    }
}

void findGreaterValues(node* current, int target) {
    if (current != nullptr) {
        if (current->data > target) {
            cout << current->data << " - ";
        }
        findGreaterValues(current->left, target);
        findGreaterValues(current->right, target);
    }
}

void displayMenu() {
    cout << endl;
    cout << "----------------------------------------------------\n";
    cout << "                BST Tree Uygulamasi\n";
    cout << "----------------------------------------------------\n";
    cout << "1 - Sayi Ekle\n";
    cout << "2 - Siralama Secenekleri\n";
    cout << "3 - Arama\n";
    cout << "4 - Silme\n";
    cout << "5 - Agac Yuksekligi\n";
    cout << "6 - En Kucuk ve En Buyuk Degerler\n";
    cout << "7 - Derinlik Ilk Traversal\n";
    cout << "8 - Dugum ve Yaprak Dugum Sayisi\n";
    cout << "9 - Agaci Temizle\n";
    cout << "10 - Belirli Degerden Kucuk Dugumleri Bul\n";
    cout << "11 - Belirli Degerden Buyuk Dugumleri Bul\n";
    cout << "0 - Cikis\n";
    cout << "----------------------------------------------------\n";
}

int main()
{
    int secim;
    while (true) {
        displayMenu();
        cout << "Secim: ";
        cin >> secim;

        switch (secim) {
        default:
            cout << "Hatali secim! Lutfen gecerli bir secim yapin.\n";
            break;
        case 0:
            cout << "Programdan cikiliyor...\n";
            clearTree(root); 
            return 0;
        case 1:
            int eklenecekSayi;
            cout << "Eklenecek Sayi: ";
            cin >> eklenecekSayi;
            Ekle(root, eklenecekSayi);
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
            if (search(aramaDeger) != nullptr) {
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
            root = deleteNode(root, silinecekDeger);
            cout << "Deger basariyla silindi.\n";
            break;
        case 5:
            cout << "Agac Yuksekligi: " << height(root) << endl;
            break;
        case 6:
            cout << "En Kucuk Deger: " << enKucukDeger(root)->data << endl;
            cout << "En Buyuk Deger: " << enKucukDeger(root)->data << endl;
            break;
        case 7:
            int targetDepth;
            cout << "ilk travel derinligi : ";
            cin >> targetDepth;
            depthFirstTraversal(root, targetDepth);
            cout << endl;
            break;
        case 8:
            cout << "Dugum Sayisi: " << countNodes(root) << endl;
            cout << "Yaprak Dugum Sayisi: " << countLeaves(root) << endl;
            break;
        case 9:
            clearTree(root);
            cout << "Agac temizlendi.\n";
            break;
        case 10:
            int targetSmaller;
            cout << "Deger : ";
            cin >> targetSmaller;
            findSmallerValues(root, targetSmaller);
            cout << endl;
            break;
        case 11:
            int targetGreater;
            cout << "Deger : ";
            cin >> targetGreater;
            findGreaterValues(root, targetGreater);
            cout << endl;
            break;
        }
    }
}
