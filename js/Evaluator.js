function PierreDellacherieEvaluator() {
    
};


PierreDellacherieEvaluator.prototype.evaluate = function(board, tetromino) {
	var tetrominoArr = tetromino.shapes[tetromino.orientation];
	
	var landingHeight = function(board, tetromino) {
        for (var i = 0; i < 4; i++) {
            for (var j = 0; j < 4; j++) {
                if (tetrominoArr[i][j] != 0) {
                    return board.length - (tetromino.y + i);
                }
            }
        }
	}
	
	var rowsEliminated = function(board, tetromino) {
        var rowNum = board.length;
        var colNum = board[0].length;

        var x = tetromino.x;
        var y = tetromino.y;
        var tetrominoArr = tetromino.shapes[tetromino.orientation];

        var eliminatedNum = 0;
        var eliminatedGridNum = 0;
        for (var i = 0; i < rowNum; i++) {
            var flag = true;
            for (var j = 0; j < colNum; j++) {
                if (board[i][j] == 0) {
                    flag = false;
                    break;
                }
            }
            if (flag === true) {
                eliminatedNum++;
                if (i >= y && i < y + 4) {
                    for (var s = 0; s < 4; s++) {
                        if (tetrominoArr[i - y][s] != 0) {
                            eliminatedGridNum++;
                        }
                    }
                }
            }
        }
        return eliminatedNum * eliminatedGridNum;
		
	}
	
	var rowTransitions = function(board) {
        var rowNum = board.length;
        var colNum = board[0].length;

        var result = 0;
        for (var i = 0; i < rowNum; i++) {
            var row_result = 0;
            var prev = 1;
            for (var j = 0; j < colNum; j++) {
                if (board[i][j] != prev) {
                    row_result++;
                    prev = board[i][j];
                }
            }
            if (prev === 0) {
                row_result++;
            }
            result += row_result;
        }

        return result;
	}
	
	var colTransitions = function(board) {
        var rowNum = board.length;
        var colNum = board[0].length;

        var result = 0;
        for (var i = 0; i < colNum; i++) {
            var col_result = 0;
            var prev = 1;
            for (var j = 0; j < rowNum; j++) {
                if (board[j][i] != prev) {
                    col_result++;
                    prev = board[j][i];
                }
            }
            if (prev === 0) {
                col_result++;
            }
            result += col_result;
        }

        return result;
	}
	
	var numHoles = function(board) {
        var rowNum = board.length;
        var colNum = board[0].length;

        var result = 0;
        for (var i = 0; i < colNum; i++) {
            var j = 0;
            var col_result = 0;
            for (; j < rowNum; j++) {
                if (board[j][i] != 0) {
                    j++;
                    break;
                }
            }
            for (; j < rowNum; j++) {
                if (board[j][i] === 0) {
                    col_result++;
                }
            }
            result += col_result++;
        }
        return result;
	}
	
	var wellSums = function(board) {
        var rowNum = board.length;
        var colNum = board[0].length;

        var i = 0, j = 0, wellDepth = 0, tDepth = 0;

        var totalWellDepth = 0;
        // leftmost wells
        wellDepth = 0;
        tDepth = 0;
        for (j = 0; j < rowNum; j++) {
            if (board[j][0] === 0 && board[j][1] != 0) {
                tDepth++;
            } 
			else {
                wellDepth += tDepth * (tDepth + 1) / 2;
                tDepth = 0;
            }
        }
        wellDepth += tDepth * (tDepth + 1) / 2;
        totalWellDepth += wellDepth;

        // middle wells
        wellDepth = 0;
        for (i = 1; i < colNum - 1; i++) {
            tDepth = 0;
            for (j = 0; j < rowNum; j++) {
                if (board[j][i] === 0 && board[j][i - 1] != 0 && board[j][i + 1] != 0) {
                    tDepth++;
                } 
				else {
                    wellDepth += tDepth * (tDepth + 1) / 2;
                    tDepth = 0;
                }
            }
            wellDepth += tDepth * (tDepth + 1) / 2;
        }
        totalWellDepth += wellDepth;

        // rightmost wells
        wellDepth = 0;
        tDepth = 0;
        for (j = 0; j < rowNum; j++) {
            if (board[j][colNum - 1] === 0 && board[j][colNum - 2] != 0) {
                tDepth++;
            } 
			else {
                wellDepth += tDepth * (tDepth + 1) / 2;
                tDepth = 0;
            }
        }
        wellDepth += tDepth * (tDepth + 1) / 2;
        totalWellDepth += wellDepth;

        return totalWellDepth;
	}
	
	
	
    return (-4.500158825082766) * landingHeight(board, tetromino)          
            + (3.4181268101392694) * rowsEliminated(board, tetromino)      
            + (-3.2178882868487753) * rowTransitions(board)            
            + (-9.348695305445199) * colTransitions(board)            
            + (-7.899265427351652) * numHoles(board)              
            + (-3.3855972247263626) * wellSums(board);            
}