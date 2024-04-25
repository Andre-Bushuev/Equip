#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <string>

using namespace std;

#include "main_Eq.h"



EquipmentContainer::EquipmentContainer(int maxSize) //Создаем вспомогательный конструктора для выделения и отчистку памяти под массив
{
	EquipmentBox = new EquipmentPtr[maxSize];

	for(int i =0 ; i <maxSize; i++)
	{
		EquipmentBox[i] = NULL;
	}

	EquipmentCount = 0;
	MaxSize = maxSize;
};

EquipmentContainer::~EquipmentContainer()
{
	for(int i =0 ; i <MaxSize; i++)
	{
		if(EquipmentBox[i] != NULL)
		{
			delete EquipmentBox[i];
			EquipmentBox[i] = NULL;
		}
	}

	delete[] EquipmentBox;
};

void EquipmentContainer::AddEquipment (EquipmentPtr newEquipment) //добавляет новое оборудование в контейнер
{
    EquipmentBox[EquipmentCount] = newEquipment;
    EquipmentCount++;
}

wstring PrintEquipmentType (const EquipmentType type)//сопоставления типа оборудования с соответствующей строкой, которая затем возвращается.
{
    switch(type)
    {
        case EquipmentType::Sports: return L"Спортивная";
        case EquipmentType::Military: return L"Военная";
        case EquipmentType::Safety: return L"Спасательная";
        case EquipmentType::Travel: return L"Путешественская";
        default: return L"неизвестный";
    }
}

wstring PrintEquipmentColor (const EquipmentColor color)//аналогично
{
    switch(color) {
        case EquipmentColor::Red: return L"Красный";
        case EquipmentColor::Orange: return L"Оранжевый";
        case EquipmentColor::Yellow: return L"Желтый";
        case EquipmentColor::Green: return L"Зеленый";
        case EquipmentColor::Blue: return L"Голубой";
        case EquipmentColor::DarkBlue: return L"Синий";
        case EquipmentColor::Violet: return L"Фиолетовый";
        default: return L"неизвестный"; }
}

wstring PrintEquipmentCountry (const EquipmentCountry country)//аналогично
{
    switch(country) {
    case EquipmentCountry::Russian: return  L"Российская";
    case EquipmentCountry::China: return  L"Китайская";
    case EquipmentCountry::Germany: return  L"Немецкая";
    case EquipmentCountry::France: return  L"Французская";
    case EquipmentCountry::Americonskay: return  L"Американская";
    default: return L"неизвестный"; }
}
wstring PrintEquipmentSize (const EquipmentSize size)//аналогично
{
    switch(size) {
    case EquipmentSize::xs_Size: return L"XS";
    case EquipmentSize::s_Size: return L"S";;
    case EquipmentSize::m_Size: return L"M";;
    case EquipmentSize::l_Size: return L"L";;
    case EquipmentSize::xl_Size: return L"XL";;
    case EquipmentSize::xxl_Size: return L"XXL";;
    default: return L"неизвестный"; }
}
Equipment *CreateEquipment(EquipmentType type) // фабричный метод
{
    switch(type)
    {
        case EquipmentType::Sports: return new Sports(static_cast<EquipmentColor>(rand() % 7), static_cast<EquipmentSize>(rand() % 6), static_cast<EquipmentCountry>(rand() % 4) );
        case EquipmentType::Military: return new Military(static_cast<EquipmentColor>(rand() % 7), static_cast<EquipmentSize>(rand() % 6), static_cast<EquipmentCountry>(rand() % 4) );
        case EquipmentType::Safety: return new Safety(static_cast<EquipmentColor>(rand() % 7), static_cast<EquipmentSize>(rand() % 6), static_cast<EquipmentCountry>(rand() % 4) );
        case EquipmentType::Travel: return new Travel(static_cast<EquipmentColor>(rand() % 7), static_cast<EquipmentSize>(rand() % 6), static_cast<EquipmentCountry>(rand() % 4) );
        default: return NULL;
    }
}

Equipment *Equipment::Create(EquipmentType type)
{
    return CreateEquipment(type);
}

// Выводит всю хорошую экпировку с ее полной характеристикой

void Task_GoodEquipment(Iterator<EquipmentPtr> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        const EquipmentPtr currentEquipment = it->GetCurrent();

        wcout << PrintEquipmentType(currentEquipment->GetType()) << L" - " << PrintEquipmentColor(currentEquipment->GetColor()) << L" - " << PrintEquipmentSize(currentEquipment->GetSize()) << L" - " << PrintEquipmentCountry(currentEquipment->GetCountry()) << L" - " << (currentEquipment->IsGood() ? L"Хорошая" : L"Плохая") << endl;
    }
}

// Покупаем хорошую одежду и только из России

void Task_BuyingGoodRussianEquipment(Iterator<EquipmentPtr> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        const EquipmentPtr currentEquipment = it->GetCurrent();

        wcout << PrintEquipmentType(currentEquipment->GetType()) << L" - " << PrintEquipmentColor(currentEquipment->GetColor())
        << L" - " << PrintEquipmentSize(currentEquipment->GetSize()) << L" - " << PrintEquipmentCountry(currentEquipment->GetCountry()) << endl;
        currentEquipment->Buy();
        wcout << L"\n" << endl;
    }
}

// Продаем новую желтую одежду размера L

void Task_SellingNewYellowEquipment(Iterator<EquipmentPtr> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        const EquipmentPtr currentEquipment = it->GetCurrent();

        if(currentEquipment->IsGood())
        {
            wcout << PrintEquipmentType(currentEquipment->GetType()) << L" - " << PrintEquipmentColor(currentEquipment->GetColor())
            << L" - " << PrintEquipmentSize(currentEquipment->GetSize()) << L" - " << PrintEquipmentCountry(currentEquipment->GetCountry())
            << L" - " << (currentEquipment->New() ? L"Новая" : L"Старая") << endl;
            currentEquipment->Sell();
            wcout << L"\n" << endl;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    wcout << L"Экипировка" << endl;

    srand(time(0)); // для оптимальной генерации экпипровки

    // Создаем контейнеры
    int boxSize = rand() % 599 + 1;

    EquipmentContainer equipmentBox(boxSize);
    MegaEquipmentContainer megaEquipmentBox;

    // Заполняем первый контейнер
    for(int i = 0; i < boxSize; i++)
    {
        equipmentBox.AddEquipment(CreateEquipment(static_cast<EquipmentType>(rand() % 4)));
    }

    // Заполняем второй контейнер
    for(int i = 0; i < rand() % 599 + 1; i++)
    {
        megaEquipmentBox.AddEquipment(CreateEquipment(static_cast<EquipmentType>(rand() % 4)));
    }

	//Выводим только хорошую экипировку с информацией о ней
	//Iterator<EquipmentPtr> *it = new EquipmentIsGoodDecorator(equipmentBox.GetIterator(), true);
	//Task_GoodEquipment(it);

	// Выводим хорошую одежду и только из России
	//Iterator<EquipmentPtr> *it = new EquipmentCountryIteratorDecorator(new EquipmentIsGoodDecorator(megaEquipmentBox.GetIterator(), true), EquipmentCountry::Russian);
	//Task_BuyingGoodRussianEquipment(it);

    // Продаем новую желтую одежду размера L

    Iterator<EquipmentPtr> *it = new EquipmentColorIteratorDecorator(new EquipmentNewDecorator(megaEquipmentBox.GetIterator(), 0), EquipmentColor::Yellow);
	Task_SellingNewYellowEquipment(it);
};
