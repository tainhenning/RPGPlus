#ifndef PLAYERSTATS_H
#def PLAYERSTATS_H
#pragma once

class PlayerStats{
	public:
		static PlayerStats* getInstance();

		PlayerStats();
		int getLevel();
		void setLevel(int lvl);

		int getStrength();
		void setStrength(int modifier);

		int getIntelligence();
		void setIntelligence(int modifier);

		int getDexterity();
		void setDexterity(int modifier);

		int getVitality();
		void setVitality(int modifier);

		int getCurrentPresses();
		void setCurrentPresses(int newPreses);

		int getCurrentHP();
		void setCurrentHP(int newHP);

		int getCurrentMP();
		void setCurrentMP(int newMP);

		int getMaxPresses();
		void setMaxPresses(int newPresses);

		int getMaxHP();
		void setMaxHP(int newHP);

		int getMaxMP();
		void setMaxMP(int newMP);

	private:
		static PlayerStats* instance;
		int strength;
		int intelligence;
		int dexterity;
		int vitality;	
		int level;
		int maxHP;
		int currentHP;
		int maxMP;
		int currentMP;
		int maxPresses;
		int currentPresses;
};

#endif