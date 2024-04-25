#ifndef Main_EqH
#define Main_EqH

#include"Equipment.h"

enum class EquipmentType: int // Создаем класс типов, цветов, стран и размеров у экипировки
{
    Sports,
    Military,
    Safety,
    Travel,
    UnknownType = -1
};

enum class EquipmentColor: int
{
    Red = 0,
    Orange = 1,
    Yellow = 2,
    Green = 3,
    Blue = 4,
    DarkBlue = 5,
    Violet = 6,
    UnknownColor = -1
};

enum class EquipmentCountry: int
{
    Russian = 0,
    China = 1,
    Germany = 2,
    France = 3,
    Americonskay = 4,
    UnknownCountry = -1,
};

enum class EquipmentSize: int
{
    xs_Size,
    s_Size,
    m_Size,
    l_Size,
    xl_Size,
    xxl_Size,
    unisex = -1
};


class Equipment // создаем кдасс экпипировки и прописываем его интерфес
{
protected: // снаружи недоступен, но наследникам класса доступен изнутри
    bool EquipmentIsGood;
    bool EquipmentNew;
    EquipmentColor Color;
    EquipmentCountry Country;
    EquipmentSize Size;

    Equipment()
    {
            EquipmentIsGood = bool  (rand() % 2);
            EquipmentNew = bool  (rand() % 2);

            Color = EquipmentColor::UnknownColor;
            Country = EquipmentCountry::UnknownCountry;
            Size = EquipmentSize::unisex;
    };
public:
    bool IsGood() const { return EquipmentIsGood; }
    bool New() const { return EquipmentNew; }

    EquipmentColor GetColor() const { return Color; }
    EquipmentCountry GetCountry() const { return Country; }
    EquipmentSize GetSize() const {return Size; }

    virtual EquipmentType GetType() const = 0;

    virtual void Use() = 0;
    virtual void Sell() = 0;
    virtual void Buy() = 0;

    static Equipment *Create(EquipmentType type);

};

typedef Equipment *EquipmentPtr;


class Sports : public Equipment //Дочерние классы у кдасса Экипировки
{
public:
    Sports(EquipmentColor color, EquipmentSize size, EquipmentCountry country) : Equipment() { Color = color; Size = size; Country = country; }

    EquipmentType GetType() const { return EquipmentType::Sports; }

    void Use() { wcout<< L"Вы испльзуйте спортивный инвентарь"; }
    void Sell() { wcout<< L"Вы продаете спортивный инвентарь"; }
    void Buy() { wcout<< L"Вы покупаете спортивный инвентарь"; }

};

class Military : public Equipment
{
public:
    Military(EquipmentColor color, EquipmentSize size, EquipmentCountry country) : Equipment() { Color = color; Size = size; Country = country; }

    EquipmentType GetType() const { return EquipmentType::Military; }

    void Use() { wcout<< L"Вы испльзуете военный инвентарь"; }
    void Sell() { wcout<< L"Вы продаете военный инвентарь"; }
    void Buy() { wcout<< L"Вы покупаете военный инвентарь"; }

};

class Safety : public Equipment
{
public:
    Safety(EquipmentColor color, EquipmentSize size, EquipmentCountry country) : Equipment() { Color = color; Size = size; Country = country; }

    EquipmentType GetType() const { return EquipmentType::Safety; }

    void Use() { wcout<< L"Вы испльзуете инвентарь для безопасности и защиты"; }
    void Sell() { wcout<< L"Вы продаете инвентарь для безопасности и защиты"; }
    void Buy() { wcout<< L"Вы покупаете инвентарь для безопасности и защиты"; }

};

class Travel : public Equipment
{
public:
    Travel(EquipmentColor color, EquipmentSize size, EquipmentCountry country) : Equipment() { Color = color; Size = size; Country = country; }

    EquipmentType GetType() const { return EquipmentType::Travel; }

    void Use() { wcout<< L"Вы испльзуете инвентарь для путешествия "; }
    void Sell() { wcout<< L"Вы продаете инвентарь для путешествия"; }
    void Buy() { wcout<< L"Вы покупаете инвентарь для путешествия"; }
};

class EquipmentContainerIterator : public Iterator<EquipmentPtr> //Первый итератор у первого контейнера(Сделан на примере лекций)
{
	private:
	const EquipmentPtr *EquipmentBox;
	int Pos;
	int Count;
	public:
	EquipmentContainerIterator(const EquipmentPtr *equipmentBox, int count)
	{
		EquipmentBox = equipmentBox;
		Count = count;
		Pos =0;
	}

	void First() {Pos =0; }
	void Next() {Pos++;}
	bool IsDone() const {return Pos >= Count;}
	EquipmentPtr GetCurrent() const {return EquipmentBox[Pos];}
};

class EquipmentContainer //Первый контейней
{
private:
    EquipmentPtr *EquipmentBox;
    int EquipmentCount;
    int MaxSize;
public:
    EquipmentContainer(int maxSize);
    virtual ~EquipmentContainer();
    void AddEquipment(EquipmentPtr newEquipment);
    int GetCount() const {return EquipmentCount;}
    EquipmentPtr GetByIndex(int index) const {return EquipmentBox[index];}

    Iterator<EquipmentPtr> * GetIterator()
    {
        return new EquipmentContainerIterator(EquipmentBox, EquipmentCount);
    }
};

class MegaEquipmentContainerIterator : public Iterator<EquipmentPtr> //Второй итератор у второго контейнера(Сделан на примере лекций)

{
	private:
	const std::list<EquipmentPtr> *EquipmentBox;
	std::list<EquipmentPtr>::const_iterator it;

	public:
	MegaEquipmentContainerIterator(const std::list<EquipmentPtr> *equipmentBox)
	{
		EquipmentBox = equipmentBox;
		it = EquipmentBox->begin();
	}
	void First(){it = EquipmentBox->begin();}
	void Next() {it++;}
	bool IsDone() const {return it == EquipmentBox->end();} //?
	EquipmentPtr GetCurrent() const { return *it; }
};


class MegaEquipmentContainer // второй контейнер
{
private:
    std::list<EquipmentPtr> EquipmentBox;
public:
    void AddEquipment (EquipmentPtr newEquipment) {EquipmentBox.push_back(newEquipment);}
    int GetCount() const {return EquipmentBox.size();}

    Iterator<EquipmentPtr> *GetIterator()
    {
        return new MegaEquipmentContainerIterator( &EquipmentBox);
    }

};

class EquipmentColorIteratorDecorator : public IteratorDecorator<EquipmentPtr> //Декоратор созданный на основе декоратора на лекции, который фильтрует объекты оборудования по типу.
{
private:
    EquipmentColor TargetColor;

public:
    EquipmentColorIteratorDecorator(Iterator<EquipmentPtr> *it, EquipmentColor targetColor) : IteratorDecorator(it)
    {
        TargetColor = targetColor;
    }

    void First()
    {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->GetColor() != TargetColor)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();
        } while (!It->IsDone() && It->GetCurrent()->GetColor() != TargetColor);
    }
};

class EquipmentCountryIteratorDecorator : public IteratorDecorator<EquipmentPtr> //Тоже декоратор созданный на примере лекции
{
private:
    EquipmentCountry targetCountry;

public:
    EquipmentCountryIteratorDecorator(Iterator<EquipmentPtr> *it, EquipmentCountry country)
        : IteratorDecorator(it), targetCountry(country) {}

    void First()
    {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->GetCountry() != targetCountry)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();
        } while (!It->IsDone() && It->GetCurrent()->GetCountry() != targetCountry);
    }
};

class EquipmentSizeIteratorDecorator : public IteratorDecorator<EquipmentPtr>//Тоже декоратор созданный на примере лекции
{
private:
    EquipmentSize targetSize;

public:
    EquipmentSizeIteratorDecorator(Iterator<EquipmentPtr> *it, EquipmentSize size)
        : IteratorDecorator(it), targetSize(size) {}

    void First()
    {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->GetSize() != targetSize)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();
        } while (!It->IsDone() && It->GetCurrent()->GetSize() != targetSize);
    }
};

class EquipmentIsGoodDecorator : public IteratorDecorator<EquipmentPtr>
{
private:
    bool TargetGood;

public:
    EquipmentIsGoodDecorator(Iterator<EquipmentPtr> *it, bool targetGood) : IteratorDecorator(it)
    {
        TargetGood = targetGood;
    }

    void First()
    {
        It->First();
        while(!It->IsDone() &&
              It->GetCurrent()->IsGood() != TargetGood)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() &&
                It->GetCurrent()->IsGood() != TargetGood);
    }
};

class EquipmentNewDecorator : public IteratorDecorator<EquipmentPtr>
{
private:
    bool TargetNew;

public:
    EquipmentNewDecorator(Iterator<EquipmentPtr> *it, bool targetNew) : IteratorDecorator(it)
    {
        TargetNew = targetNew;
    }

    void First()
    {
        It->First();
        while(!It->IsDone() &&
              It->GetCurrent()->New() != TargetNew)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() &&
                It->GetCurrent()->New() != TargetNew);
    }
};

#endif
