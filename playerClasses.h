
class Novice
{
	public:
		Novice();
		getStrength(int baseStrength, int level);
		getMagic(int baseMagic, int level);
		getDexterity(int baseDexterity, int level);
	private:
		int level;
		const int attackModifier = 1;
		const int magicModifier = 1;
		const int dexterityModifier = 1;
		const int vitalityModifier = 1;

}
class BlackMage
{
	public:
		BlackMage();
		getStrength(int baseStrength, int level);
		getMagic(int baseMagic, int level);
		getDexterity(int baseDexterity, int level);
	private:
		int level;
		const int attackModifier = 1;
		const int magicModifier = 5;
		const int dexterityModifier = 1;
		const int vitalityModifier = 1;


}
class WhiteMage
{
	public:
		WhiteMage();
		getStrength(int baseStrength, int level);
		getMagic(int baseMagic, int level);
		getDexterity(int baseDexterity, int level);
	private:
		int level;
		const int attackModifier = 1;
		const int magicModifier = 5;
		const int dexterityModifier = 1;
		const int vitalityModifier = 1;

}
class Warrior
{
	public:
		Warrior();
		getStrength(int baseStrength, int level);
		getMagic(int baseMagic, int level);
		getDexterity(int baseDexterity, int level);
	private:
		int level;
		const int attackModifier = 5;
		const int magicModifier = 1;
		const int dexterityModifier = 1;
		const int vitalityModifier = 5;

}
class Monk
{
	public:
		Monk();
		getStrength(int baseStrength, int level);
		getMagic(int baseMagic, int level);
		getDexterity(int baseDexterity, int level);
	private:
		int level;
		const int attackModifier = 5;
		const int magicModifier = 1;
		const int dexterityModifier = 1;
		const int vitalityModifier = 3;

}
class Duelist
{
	public:
		Duelist();
		getStrength(int baseStrength, int level);
		getMagic(int baseMagic, int level);
		getDexterity(int baseDexterity, int level);
	private:
		int level;
		const int attackModifier = 1;
		const int magicModifier = 1;
		const int dexterityModifier = 5;
		const int vitalityModifier = 3;

}