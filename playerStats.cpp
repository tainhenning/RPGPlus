PlayerStats* PlayerStats::instance = 0;

PlayerStats* PlayerStats::getInstance()
{
	if(instance == 0)
	{
		instance = new Singleton();
	}
	return instance;
}
PlayerStats::PlayerStats()
{
	level = 1;
	strength = 1;
	dexterity = 1;
	intelligence = 1;
	vitality = 1;
	currentPresses = 5;
	maxPresses = 5;
	maxHP = vitality * 25;
	currentHP = maxHP;
	maxMP = intelligence * 25;
	currentMP = maxMP;
}
int PlayerStats::getLevel()
{
	return level;
}
void PlayerStats::setLevel(int lvl)
{
	level = lvl;
}
int PlayerStats::getStrength()
{
	return strength;
}
void PlayerStats::setStrength(int level, int modifier)
{
	strength = level * modifier
}
int PlayerStats::getIntelligence()
{
	return intelligence;
}
void PlayerStats::setIntelligence(int level, int modifier)
{
	intelligence = level * modifier;
}
int PlayerStats::getDexterity()
{
	return dexterity;
}
void PlayerStats::setDexterity(int level, int modifier)
{
	dexterity = level * modifier;
}
int PlayerStats::getVitality()
{
	return vitality;
}
void PlayerStats::setVitality(int level, int modifier)
{
	vitality = level * modifier;
}
int PlayerStats::getCurrentPresses()
{
	return currentPresses;
}
void PlayerStats::setCurrentPresses(int newPresses)
{
	currentPresses = newPresses;
}

int PlayerStats::getCurrentHP()
{
	return currentHP;
}
void PlayerStats::setCurrentHP(int newHP)
{
	currentHP = newHP;
}

int PlayerStats::getCurrentMP()
{
	return currentMP;
}
void PlayerStats::setCurrentMP(int newMP)
{
	currentMP = newMP;
}

int PlayerStats::getMaxPresses()
{
	return maxPresses;
}
void PlayerStats::setMaxPresses(int newPresses)
{
	maxPresses = newPresses;
}

int PlayerStats::getMaxHP()
{
	return maxHP;
}
void PlayerStats::setMaxHP(int newHP)
{
	maxHP = newHP;
}

int getMaxMP();
{
	return maxMP;
}
void setMaxMP(int newMP)
{
	maxMP = newMP;
}