var CommandType = {
	LEFT:1,
    RIGHT:2,
    UP:3,
    DOWN:4
};

function Tetromino(x, y, shape_idx, color, shapes, orientation) {
	this.shape_idx = shape_idx
	this.shapes = shapes
	this.orientation = orientation
	this.color = color
	this.x = x
	this.y = y		
}
	
Tetromino.prototype.render = function(ctx) {
    var tetrominoArr = this.shapes[this.orientation];
	
    for (var i = 0; i < 4; i++) {
        for (var j = 0; j < 4; j++) {
            if (tetrominoArr[i][j] == 1) {
				ctx.fillStyle = "hsl(" + this.color + ",100%,50%)";
		    	ctx.fillRect((this.x + j) * 20, (this.y + i) * 20, 20, 20);

                ctx.strokeStyle = "rgb(255, 255, 255)";
                ctx.strokeRect((this.x + j) * 20, (this.y + i) * 20, 20, 20);
            }
        }
    }
}
	
Tetromino.prototype.executeCommand = function(cmd) {
    switch(cmd) {
        case CommandType.LEFT:
            this.x--;
            break;
        case CommandType.RIGHT:
            this.x++;
            break;
        case CommandType.UP:
            this.orientation = (this.orientation + 1) % 4;
            break;
        case CommandType.DOWN:
            this.y++;
            break;
    }
};
	
LTetromino.SHAPES = [
    [
        [0, 1, 0, 0],
        [0, 1, 0, 0],
        [0, 1, 1, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 0, 0, 0],
        [1, 1, 1, 0],
        [1, 0, 0, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 1, 1, 0],
        [0, 0, 1, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 0, 0, 0],
        [0, 0, 1, 0],
        [1, 1, 1, 0],
        [0, 0, 0, 0]
    ]
]
JTetromino.SHAPES = [
    [
        [0, 0, 1, 0],
        [0, 0, 1, 0],
        [0, 1, 1, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 1, 0, 0],
        [0, 1, 1, 1],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 1, 1, 0],
        [0, 1, 0, 0],
        [0, 1, 0, 0],
        [0, 0, 0, 0]
    ],
    [
        [1, 1, 1, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ]
]
ITetromino.SHAPES = [
    [
        [0, 0, 0, 0],
        [1, 1, 1, 1],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 0, 1, 0],
        [0, 0, 1, 0],
        [0, 0, 1, 0],
        [0, 0, 1, 0]
    ],
    [
        [0, 0, 0, 0],
        [1, 1, 1, 1],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 0, 1, 0],
        [0, 0, 1, 0],
        [0, 0, 1, 0],
        [0, 0, 1, 0]
    ]
]
OTetromino.SHAPES = [
    [
        [0, 0, 0, 0],
        [0, 1, 1, 0],
        [0, 1, 1, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 0, 0, 0],
        [0, 1, 1, 0],
        [0, 1, 1, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 0, 0, 0],
        [0, 1, 1, 0],
        [0, 1, 1, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 0, 0, 0],
        [0, 1, 1, 0],
        [0, 1, 1, 0],
        [0, 0, 0, 0]
    ]
]
TTetromino.SHAPES = [
    [
        [0, 0, 0, 0],
        [0, 1, 0, 0],
        [1, 1, 1, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 0, 0, 0],
        [0, 1, 0, 0],
        [1, 1, 0, 0],
        [0, 1, 0, 0]
    ],
    [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [1, 1, 1, 0],
        [0, 1, 0, 0]
    ],
    [
        [0, 0, 0, 0],
        [0, 1, 0, 0],
        [0, 1, 1, 0],
        [0, 1, 0, 0]
    ]
]
STetromino.SHAPES = [
    [
        [0, 0, 0, 0],
        [0, 1, 1, 0],
        [1, 1, 0, 0],
        [0, 0, 0, 0]
    ],
    [
        [1, 0, 0, 0],
        [1, 1, 0, 0],
        [0, 1, 0, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 0, 0, 0],
        [0, 1, 1, 0],
        [1, 1, 0, 0],
        [0, 0, 0, 0]
    ],
    [
        [1, 0, 0, 0],
        [1, 1, 0, 0],
        [0, 1, 0, 0],
        [0, 0, 0, 0]
    ]   
]
ZTetromino.SHAPES = [
    [
        [0, 0, 0, 0],
        [1, 1, 0, 0],
        [0, 1, 1, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 0, 1, 0],
        [0, 1, 1, 0],
        [0, 1, 0, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 0, 0, 0],
        [1, 1, 0, 0],
        [0, 1, 1, 0],
        [0, 0, 0, 0]
    ],
    [
        [0, 0, 1, 0],
        [0, 1, 1, 0],
        [0, 1, 0, 0],
        [0, 0, 0, 0]
    ]
]
	
function LTetromino(x, y, orientation) {
    Tetromino.call(this, x, y, 1, 40, LTetromino.SHAPES, orientation);
};
// class LTetrominoextend Tetromino
LTetromino.prototype = new Tetromino();

function JTetromino(x, y, orientation) {
    Tetromino.call(this, x, y, 2, 240, JTetromino.SHAPES, orientation);
};

JTetromino.prototype = new Tetromino();

function ITetromino(x, y, orientation) {
    Tetromino.call(this, x, y, 3, 180, ITetromino.SHAPES, orientation);
};

ITetromino.prototype = new Tetromino();

function OTetromino(x, y, orientation) {
    Tetromino.call(this, x, y, 4, 60, OTetromino.SHAPES, orientation);
};

OTetromino.prototype = new Tetromino();

function TTetromino(x, y, orientation) {
    Tetromino.call(this, x, y, 5, 280, TTetromino.SHAPES, orientation);
};

TTetromino.prototype = new Tetromino();

function STetromino(x, y, orientation) {
    Tetromino.call(this, x, y, 6, 120, STetromino.SHAPES, orientation);
};

STetromino.prototype = new Tetromino();

function ZTetromino(x, y, orientation) {
    Tetromino.call(this, x, y, 7, 0, ZTetromino.SHAPES, orientation);
};

ZTetromino.prototype = new Tetromino();

