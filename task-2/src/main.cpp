#include "LifeGame.h"
#include "LifeGameParser.h"

int main(int argc, char** argv) {
    bool parsingErrors[6] = {0};
    LifeGameParser lifeGameParser;
    ParseFileStatus status = lifeGameParser.parseLifeFile(argc, argv, parsingErrors);
    LifeGame game = LifeGame(lifeGameParser.getBirthCondition(), lifeGameParser.getSurvivalCondition(),
                             lifeGameParser.getRow(), lifeGameParser.getColumn(), lifeGameParser.getGrid(),
                             lifeGameParser.getUniverseName(), status, parsingErrors,
                             lifeGameParser.getFilename(),lifeGameParser.getIterationsOffline());
    game.startGame();
	return 0;
}