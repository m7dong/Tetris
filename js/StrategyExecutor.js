function StrategyExecutor() {
	this.movements = new Movements();
	this.evaluator = new PierreDellacherieEvaluator();
}


StrategyExecutor.prototype.makeBestDecision = function(game, tetromino) {
    var bestMove = null;
    var bestScore = -1000000;
 
 
    // find all landing position and paths
    var allMovements = this.movements.getAllMovements(game, tetromino);
 
    // find the best landing position
    for (var i = 0; i < allMovements.length; i++) {
        var landing_pos = allMovements[i].final_position;
 
        var tetrominoArr = tetromino.shapes;
        var board_copy = game.addTetrominoBoardCopy(landing_pos.x, landing_pos.y, tetrominoArr[landing_pos.orientation]);
 	   
        // evaluate each landing point
		var landing_tetromino = new Tetromino(landing_pos.x, landing_pos.y, tetromino.shape_idx, 
											  tetromino.color, tetromino.shapes, landing_pos.orientation)
        var tscore = this.evaluator.evaluate(board_copy, landing_tetromino);
 
        // update the best path
        if (bestMove === null || tscore > bestScore) {
            bestScore = tscore;
            bestMove = allMovements[i].path;
        }
    }
 
    // return the best landing point and the path
    return {score:bestScore, action_moves:bestMove};
 
 } 