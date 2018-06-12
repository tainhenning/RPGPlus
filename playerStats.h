#ifndef PLAYERSTATS_H
#def PLAYERSTATS_H
#pragma once

class playerStats{
	public:
		playerStats();
		int getStrength();
		void setStrength(int level, int modifier);

		int getIntelligence();
		void setIntelligence(int level, int modifier);

		int getDexterity();
		void setDexterity(int level, int modifier);

		int getVitality();
		void setVitality(int level, int modifier);

	private:
		int strength;
		int intelligence;
		int dexterity;
		int vitality;	
};

#endif