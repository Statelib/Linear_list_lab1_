#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

// Структура узла списка
struct Node {
    double data; // data - числовое значение(коэффициент)
    Node* next; // указатель на следующий элемент (адрес)

    // создание конструктора, узел с заданным значением 
    Node(double val) : data(val), next(nullptr) {}
};

// Класс линейного списка, каждый элемент указывает на следующий
class LinkedList {
private:
    Node* head; // указатель на первый узел списка
    int size; // количество элементов списка

public:
    LinkedList() : head(nullptr), size(0) {} //  инилиализация пустого списка с помощью конструктора

    // Деструктор освобождение выделенной памяти 
    ~LinkedList() {
        clear();
    }

    // Добавление элемента в конец списка
    void append(double value) {
        Node* newNode = new Node(value); // создание нового объекта узла, выделение памяти
        if (!head) { // head == nullptr 
            head = newNode;
        }
        else {
            Node* current = head; // проверка элемента ( последний узел) next == nullptr
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    // Добавление элемента в начало списка
    void prepend(double value) {
        // создание нового узла 
        Node* newNode = new Node(value);
        // указатель на старый head
        newNode->next = head;
        head = newNode;
        size++;
    }

    // Удаление элемента по индексу
    bool remove(int index) {
        if (index < 0 || index >= size || !head) {
            return false;
        }
        // удаление первого элемента
        if (index == 0) {
            Node* temp = head; // сохранение алреса head
            head = head->next; // 
            delete temp; // освобождение памяти
            size--;
            return true;
        }
        // удаление элемента в середине/конце
        Node* current = head;
        // находим узел перед удаляемым
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        // current указывает на узел перед удаляемым
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        size--;
        return true;
    }

    // Получить элемент по индексу
    double get(int index) const {
        if (index < 0 || index >= size) {
            return 0.0;
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Вывод обычного списка
    void display(const string& name = "Список") const {
        cout << name << ": ";
        if (!head) {
            cout << "пуст" << endl;
            return;
        }

        Node* current = head;
        cout << "[ ";
        while (current) {
            cout << fixed << setprecision(2) << current->data;
            if (current->next) cout << ", ";
            current = current->next;
        }
        cout << " ]" << endl;
    }

    // Вывод списка с индексами
    void displayWithIndices() const {
        if (!head) {
            cout << "Список пуст" << endl;
            return;
        }

        Node* current = head;
        int index = 0;
        while (current) {
            cout << "[" << index << "] = " << fixed << setprecision(2) << current->data << endl;
            current = current->next;
            index++;
        }
    }

    // Вывод списка как многочлена с отображением степеней
    void displayAsPolynomial(const string& name = "P(x)") const {
        cout << name << " = ";
        if (!head) {
            cout << "0" << endl;
            return;
        }

        Node* current = head;
        int degree = size - 1; //начальная степень 
        bool first = true; // флаг для первого элемента

        while (current) {
            double coef = current->data;

            if (abs(coef) > 1e-9) {
                if (!first && coef > 0) {
                    cout << " + ";
                }
                else if (coef < 0) {
                    cout << " - ";
                    coef = -coef;
                }

                if (degree == 0 || abs(coef - 1.0) > 1e-9) {
                    cout << fixed << setprecision(2) << coef;
                }

                if (degree > 0) {
                    cout << "x";
                    if (degree > 1) {
                        cout << "^" << degree;
                    }
                }

                first = false;
            }

            current = current->next;
            degree--;
        }

        if (first) {
            cout << "0";
        }

        cout << endl;
    }

    // Проверка, является ли число целым
    bool isInteger(double num) const {
        return abs(num - round(num)) < 1e-9; // abs(7.0 - 7) 
    }

    // Получение целой части
    double getWholePart(double num) const { // округление вниз до ближайшего целого
        return floor(num);
    }

    // Получение дробной части
    double getFractionalPart(double num) const {
        return num - floor(num); // вычитание из числа его целую часть
    }

    // Обработка списка: создание списков B и K
    void processLists(LinkedList& B, LinkedList& K) const {
        Node* current = head;

        while (current) {
            double value = current->data;
            // проверка, целое ли число 
            if (!isInteger(value)) {
                B.append(getWholePart(value)); // целая в B
                K.append(getFractionalPart(value)); // дробная в K
            }

            current = current->next;
        }
    }

    // Очистка списка
    void clear() {
        while (head) {
            Node* temp = head; // сохранение адреса head
            head = head->next; // 
            delete temp; // освобождаем память
        }
        size = 0;
    }

    // Получение размера
    int getSize() const {
        return size;
    }

    // Проверка на пустоту (head == nullptr)
    bool isEmpty() const {
        return head == nullptr;
    }
};

// Функция для очистки буфера ввода
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Пауза
void pause() {
    cout << "\nНажмите Enter...";
    clearInputBuffer();
    cin.get();
}

int main() {
    setlocale(LC_ALL, "Russian");

    LinkedList A; // исходная последовательность 
    LinkedList B; // целые
    LinkedList K; // дробные 

    int choice;

    cout << "  РАБОТА С ЛИНЕЙНЫМИ СПИСКАМИ" << endl;

    do {
        cout << "\n Меню" << endl;
        cout << "1. Создать список A" << endl;
        cout << "2. Добавить элемент в A" << endl;
        cout << "3. Удалить элемент из A" << endl;
        cout << "4. Показать список A" << endl;
        cout << "5. Обработать список (создать B и K)" << endl;
        cout << "6. Показать все списки" << endl;
        cout << "7. Показать как многочлены" << endl;
        cout << "0. Выход" << endl;
        cout << "\nВыбор:      ";
        cin >> choice;

        if (cin.fail()) {
            clearInputBuffer();
            cout << "Ошибка ввода!\n";
            continue;
        }

        switch (choice) {
        case 1: {
            A.clear();
            int mode;
            cout << "\n1 - Тестовые данные" << endl;
            cout << "2 - Ввести вручную" << endl;
            cout << "Выбор: ";
            cin >> mode;

            if (mode == 2) {
                int n;
                cout << "Количество элементов: ";
                cin >> n;

                if (cin.fail() || n <= 0) {
                    clearInputBuffer();
                    cout << "Ошибка!\n";
                    break;
                }

                for (int i = 0; i < n; i++) {
                    double value;
                    cout << "Элемент " << (i + 1) << ": ";
                    cin >> value;

                    if (cin.fail()) {
                        clearInputBuffer();
                        cout << "Ошибка! Начните заново.\n";
                        A.clear();
                        break;
                    }
                    A.append(value);
                }
            }
            else {
                A.append(3.14);
                A.append(5.67);
                A.append(2.89);
                A.append(7.0);
                A.append(4.25);
                A.append(8.91);
            }

            cout << "\nСписок создан!\n";
            A.display("A");
            pause();
            break;
        }

        case 2: {
            if (A.isEmpty()) {
                cout << "\nСписок пуст! Сначала создайте список.\n";
                pause();
                break;
            }

            double value;
            int where;
            cout << "\n1 - В конец" << endl;
            cout << "2 - В начало" << endl;
            cout << "Выбор: ";
            cin >> where;

            cout << "Значение: ";
            cin >> value;

            if (cin.fail()) {
                clearInputBuffer();
                cout << "Ошибка!\n";
            }
            else {
                if (where == 2) {
                    A.prepend(value);
                    cout << "Добавлено в начало!\n";
                }
                else {
                    A.append(value);
                    cout << "Добавлено в конец!\n";
                }
                A.display("A");
            }
            pause();
            break;
        }

        case 3: {
            if (A.isEmpty()) {
                cout << "\nСписок пуст!\n";
                pause();
                break;
            }

            cout << "\nТекущий список:\n";
            A.displayWithIndices();

            int index;
            cout << "\nИндекс для удаления: ";
            cin >> index;

            if (cin.fail()) {
                clearInputBuffer();
                cout << "Ошибка!\n";
            }
            else {
                if (A.remove(index)) {
                    cout << "Удалено!\n";
                    A.display("A");
                }
                else {
                    cout << "Неверный индекс!\n";
                }
            }
            pause();
            break;
        }

        case 4: {
            cout << "\n";
            A.display("A");
            cout << "Размер: " << A.getSize() << endl;
            pause();
            break;
        }

        case 5: {
            if (A.isEmpty()) {
                cout << "\nСписок A пуст!\n";
                pause();
                break;
            }

            B.clear();
            K.clear();
            A.processLists(B, K);

            cout << "\nОБРАБОТКА ЗАВЕРШЕНА \n";
            cout << "\nИсходный список:" << endl;
            A.display("A");

            cout << "\nРезультаты:" << endl;
            B.display("B (целые части)");
            K.display("K (дробные части)");

            cout << "\nОбработано нецелых чисел: " << B.getSize() << endl;
            cout << "Пропущено целых чисел: " << (A.getSize() - B.getSize()) << endl;
            pause();
            break;
        }

        case 6: {
            cout << "\n ВСЕ СПИСКИ \n";
            A.display("A");
            B.display("B");
            K.display("K");
            cout << "\nРазмеры: A=" << A.getSize()
                << ", B=" << B.getSize()
                << ", K=" << K.getSize() << endl;
            pause();
            break;
        }

        case 7: {
            cout << "\nМНОГОЧЛЕНЫ\n";
            cout << "Каждый элемент списка = коэффициент многочлена\n\n";
            A.displayAsPolynomial("P_A(x)");
            B.displayAsPolynomial("P_B(x)");
            K.displayAsPolynomial("P_K(x)");
            pause();
            break;
        }

        case 0:
            cout << "\nВыход из программы.\n";
            break;

        default:
            cout << "\nНеверный выбор! \n";
            pause();
        }

    } while (choice != 0);

    return 0;
}