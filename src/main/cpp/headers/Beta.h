#ifndef BETA_H_
#define BETA_H_

class Beta {
public:
	static void startup();
	static void shutdown();
	static void runGame(Game* g);
	static void execute(Motor *x, Motor *y, Motor *z) = 0;

private:
	static Game *game;
	static bool isRunning;
};

class Game {
	public: Game() {}
	virtual void tick() = 0;
	virtual void execute(Motor *x, Motor *y, Motor *z) = 0;
};
#endif