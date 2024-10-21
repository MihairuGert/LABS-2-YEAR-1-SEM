#include "LifeGame.h"
#include "LifeGameParser.h"

int main(int argc, char** argv) {
    bool parseLifeFileStatus[6] = {0};
    LifeGameParser lifeGameParser;
    ParseFileStatus status = lifeGameParser.parseLifeFile(argc, argv, parseLifeFileStatus);
    LifeGame game = LifeGame(lifeGameParser.getBirthCondition(), lifeGameParser.getSurvivalCondition(),
                             lifeGameParser.getRow(), lifeGameParser.getColumn(), lifeGameParser.getGrid1(),
                             lifeGameParser.getUniverseName(), status, parseLifeFileStatus,
                             lifeGameParser.getFilename(),lifeGameParser.getIterationsOffline());
    game.startGame();
	return 0;
}