(function(window) {	
    var tetrominoTypes = [LTetromino, JTetromino, ITetromino, OTetromino, TTetromino, STetromino, ZTetromino];
	var tetrominoColor = [40, 240, 180, 60, 280, 120, 0]
	
    function newTetromino() {
        var tetrominoIdx = Math.floor(Math.random() * 100) % tetrominoTypes.length;
        var tetrominoOrientation = Math.floor(Math.random() * 100) % 4;

        return new tetrominoTypes[tetrominoIdx](0, 0, tetrominoOrientation);
    }
	
	function Game() {
        this.row = 20;
        this.col = 10;
		this.strategyExecutor = new StrategyExecutor()
		this.moves = [];
		
		this.board = new Array(this.row);
        for (var i = 0; i < this.row; i++) {
            this.board[i] = new Array(this.col);
            for (var j = 0; j < this.col; j++) {
                this.board[i][j] = 0;
            }
        }
		
        this.board_copy = new Array(this.row);
        for (var i = 0; i < this.row; i++) {
            this.board_copy[i] = new Array(this.col);
            for (var j = 0; j < this.col; j++) {
                this.board_copy[i][j] = 0;
            }
        }
		
		this.currentTetromino = null
		this.nextTetromino = null
		
		//this.score = 0
		this.timestamp = new Date().getTime();
	}
	
    Game.prototype.render = function(ctx) {
        for (var i = 0; i < this.row; i++) {
            for (var j = 0; j < this.col; j++) {
                if (this.board[i][j] != 0) {
                    ctx.fillStyle = "hsl(" + tetrominoColor[this.board[i][j]-1] + ",100%,50%)";
					ctx.fillRect(j * 20, i * 20, 20, 20);
					
	                ctx.strokeStyle = "rgb(255, 255, 255)";
	                ctx.strokeRect(j * 20, i * 20, 20, 20);				
                }
				else {
					ctx.fillStyle = "rgb(68, 68, 68)";
					ctx.fillRect(j * 20, i * 20, 20, 20);
				}
            }
        }

        if ( this.currentTetromino != null ) {
            this.currentTetromino.render(ctx);
        }

    };
	
    Game.prototype.addTetrominoBoardCopy = function(x, y, tetrominoArr) {
        var i, j;
        for (i = 0; i < this.row; i++) {
            for (j = 0; j < this.col; j++) {
                this.board_copy[i][j] = this.board[i][j];
            }
        }

        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (tetrominoArr[i][j] === 1) {
                    if (x + j < 0 || x + j >= this.col || y + i < 0 || y + i >= this.row) {
                        continue;
                    }
                    this.board_copy[y + i][x + j] = 1;
                }
            }
        }
        return this.board_copy;
    }
	
    Game.prototype.start = function() {
        for (var i = 0; i < this.row; i++) {
            for (var j = 0; j < this.col; j++) {
                this.board[i][j] = 0;
            }
        }
		
        this.currentTetromino = newTetromino();
        this.nextTetromino = newTetromino();

        //this.score = 0;

        this.timestamp = new Date().getTime();

        var moveArr = this.strategyExecutor.makeBestDecision(this, this.currentTetromino);
        this.moves = moveArr.action_moves;

    }
	
    Game.prototype.checkAvailable = function(x, y, tetrominoArr) {		
        for ( var i = 0; i < 4; i++ ) {
            for ( var j = 0; j < 4; j++ ) {
                if (tetrominoArr[i][j] == 1) {
                    if (x + j < 0 || x + j >= this.col || y + i < 0 || y + i >= this.row ) {
                        return false;
                    }
                    if ( this.board[y + i][x + j] != 0 ) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
	
    Game.prototype.checkMove = function(cmd) {

        var orientation = this.currentTetromino.orientation;
        var x = this.currentTetromino.x;
        var y = this.currentTetromino.y;

        switch(cmd) {
            case CommandType.LEFT:
                x = this.currentTetromino.x - 1;
                break;
            case CommandType.RIGHT:
                x = this.currentTetromino.x + 1;
                break;
            case CommandType.UP:
                orientation = (this.currentTetromino.idx + 1) % 4;
                break;
            case CommandType.DOWN:
                y = this.currentTetromino.y + 1;
                break;
        }
        var tetrominoArr = this.currentTetromino.shapes[orientation];

        return this.checkAvailable(x, y, tetrominoArr);

    };
	
    Game.prototype.land = function(x, y, tetrominoArr) {
        for (var i =0; i < 4; i++) {
            for (var j = 0; j < 4; j++) {
                if (tetrominoArr[i][j] == 1) {
                    if (x + j < 0 || x + j >= this.col || y + i < 0 || y + i >= this.row) {
                        continue;
                    }
                    this.board[y + i][x + j] = this.currentTetromino.shape_idx;
                }
            }
        }

        // eliminate filled rows
		
        var eliminateNum = 0;
        var eliminateArr = new Array(this.row);
        for (var i = this.row - 1; i >= 0; i--) {
            var gridNum = 0;
            for (var j = 0; j < this.col; j++) {
                if (this.board[i][j] == 0) {
                    break;
                }
                gridNum++;
            }
            // satisfy elimination rule
            if (gridNum === this.col) {
                eliminateArr[i] = true;
                eliminateNum++;
            } 
			else {
                eliminateArr[i] = false;
            }
        }

        if (eliminateNum > 0) {
            var nextIdx = this.row - 1;
            for (var i = this.row - 1; i >= 0; i--) {
                while (nextIdx >= 0 && eliminateArr[nextIdx] === true) {
                    nextIdx--;
                }

                if (i === nextIdx) {
                    nextIdx--;
                    continue;
                } 
				else {
                    if (nextIdx >= 0) {
                        for (var j = 0; j < this.col; j++) {
                            this.board[i][j] = this.board[nextIdx][j];
                        }
                        nextIdx--;
                    } 
					else {
                        for (var j = 0; j < this.col; j++) {
                            this.board[i][j] = 0;
                        }
                    }
                }
            }
        }

        return eliminateNum;  
    }
	
    Game.prototype.update = function() {
        var now = new Date().getTime();
        if (now - this.timestamp > 500) {
            if (this.currentTetromino != null) {
                if (this.moves.length > 0) {
                    this.currentTetromino.x = this.moves[0].x;
                    this.currentTetromino.y = this.moves[0].y;
                    this.currentTetromino.orientation = this.moves[0].orientation;
                    this.moves.splice(0, 1);
                } 
				else if (this.checkMove(CommandType.DOWN)) {
                    this.currentTetromino.executeCommand(CommandType.DOWN);
                } 
				else {
                    var x = this.currentTetromino.x;
                    var y = this.currentTetromino.y;
                    var tetrominoArr = this.currentTetromino.shapes[this.currentTetromino.orientation];

                    var eliminatedLines = this.land(x, y, tetrominoArr);
                    //this.updateScore(eliminatedLines);

                    this.currentTetromino = this.nextTetromino;
                    this.nextTetromino = newTetromino();

                    if (this.isGameOver()) {
                        alert("Game Over\n you had " + this.score + " points");
                        this.initGame();
                    } 
					else {
                        var moveArr = this.strategyExecutor.makeBestDecision(this, this.currentTetromino);
                        this.moves = moveArr.action_moves;
                    }

                }
            }
            this.timestamp = now;
        } 
		else {
            if (this.moves.length > 0) {
                if (this.moves[0].x === this.currentTetromino.x
                    && this.moves[0].y === this.currentTetromino.y + 1
                    && this.moves[0].orientation === this.currentTetromino.orientation) {
                    this.currentTetromino.y = this.moves[0].y;
                    this.moves.splice(0, 1);
                }
            }
        }

    };
	
	
    Game.prototype.isGameOver = function() {
		var tetrominoArr = this.currentTetromino.shapes[this.currentTetromino.orientation];
		var x = this.currentTetromino.x
		var y = this.currentTetromino.y
        for (var i =0; i < 4; i++) {
            for (var j = 0; j < 4; j++) {
                if (tetrominoArr[i][j] == 1) {
                    if (x + j < 0 || x + j >= this.col || y + i < 0 || y + i >= this.row) {
                        continue;
                    }
                    if (this.board[y + i][x + j] != 0) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
	
    function gameLogic() {
        game.update();
        game.render(ctx);
    }
	
    var gameCanvas = document.getElementById("gameCanvas");
    var ctx = gameCanvas.getContext("2d");

    var game = new Game();
    game.start();

    var fps = 60;
    setInterval(gameLogic, fps);
	
			
})(window);