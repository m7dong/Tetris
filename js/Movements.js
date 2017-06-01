function Movements() {
	
}

Movements.prototype.getAllMovements = function(game, tetromino) {
	var hashTetromino = function(x, y, orientation) {
		return "" + x + "," + y + "," + orientation;
	}
	
	var board = game.board
	var numRow = game.row
	var numVol = game.col
	var tetrominoArr = tetromino.shapes
	
	var positions = []
	positions.push({x:tetromino.x, y:tetromino.y, orientation:tetromino.orientation, prev:-1})
	var visited = {}
	visited[hashTetromino(tetromino.x, tetromino.y, tetromino.orientation)] = true;
	var all_moves = []
	
	var checkPotentialMove = function(px, py, po, curr_pos) {
		if (game.checkAvailable(px, py, tetrominoArr[po]) ) {
			var key = hashTetromino(px, py, po);
		    if (!visited.hasOwnProperty(key)) {
		    	positions.push({x:px, y:py, orientation:po, prev:curr_pos});
		        visited[key] = true;
		    }
			return true
		}
		else {
			return false
		}
	}
	
	var curr_idx = 0
	while (curr_idx < positions.length) {
		var curr_pos = positions[curr_idx];
		
		// check if tetromino can move to the left
		var px = curr_pos.x - 1;
		var py = curr_pos.y;
		var po = curr_pos.orientation;
		checkPotentialMove(px, py, po, curr_pos);
		
		// check if tetromino can move to the right
		px = curr_pos.x + 1;
		py = curr_pos.y;
		po = curr_pos.orientation;
		checkPotentialMove(px, py, po, curr_pos);
		
		// check if tetromino can rotate
		px = curr_pos.x;
		py = curr_pos.y;
		po = (curr_pos.orientation + 1) % 4;
		checkPotentialMove(px, py, po, curr_pos);
		
		// check if tetromino can move down 
		px = curr_pos.x;
		py = curr_pos.y + 1;
		po = curr_pos.orientation;
		if(!checkPotentialMove(px, py, po, curr_pos)) {
			var path = []
			
			path.push({x:curr_pos.x, y: curr_pos.y, orientation: curr_pos.orientation});
			var prev_node = curr_pos.prev;
			while (prev_node != -1) {
				path.push({x: prev_node.x, y: prev_node.y, orientation: prev_node.orientation});
			    prev_node = prev_node.prev;
			}
			path.reverse();
			all_moves.push({final_position: curr_pos, path: path})
		}
		
		curr_idx = curr_idx + 1;
		
	}
	
	return all_moves;
	
}


