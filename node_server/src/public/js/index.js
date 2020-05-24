(function () {
  var BOARD_SIZE = 20;

  function onLoadWindow() {
    var board = [];
    for (var i = 0; i < BOARD_SIZE; i++) {
      var row = [];

      for (var j = 0; j < BOARD_SIZE; j++) {
        row.push("");
      }
      board.push(row);
    }

    var app = new Vue({
      el: "#app",
      data: {
        arrayInfo: window.data,
        board: board,
        bot: window.data[0],
        currentStep: 0,
        clearId: null,
        active: false,
        botNumber: 0
      },
      created: function(){
        var step = this.bot.dna[0];
        this.board[step.i][step.j] = "A";
      },
      methods: {
        toggleActive: function(){
          this.toggleTileState(0,0,);
        },
        clearBoard: function() {
          for(var i=0; i < BOARD_SIZE; i++) {
            for(var j=0; j< BOARD_SIZE; j++ ) {
              this.board[i][j] = "";
            }
          }
        },
        stopAnimation: function(){
          clearInterval(this.clearId);
          this.clearId = null;
          this.botNumber++;
          if(this.botNumber >= this.arrayInfo.length) {
            console.log('FINISHED');
            return;
          }

          console.log('Finished Bot: '+ this.botNumber );
          console.timeEnd("moving");
          this.bot = this.arrayInfo[this.botNumber];
          this.currentStep = 0;
          var step = this.bot.dna[0];
          this.board[step.i][step.j] = "A";
          app.$forceUpdate();
          this.startAnimation();
        },
        toggleTileState: function(i, j) {
          this.board[i][j] = this.board[i][j] === 'A' ? '' : 'A';
          app.$forceUpdate();
        },
        startAnimation: function() {
          console.time("moving")
          if (!this.clearId) {
            var self = this;
            this.clearId = setInterval(function () {
              self.currentStep++;
              if(self.currentStep >=  self.bot.dna.length){
                setTimeout(function() {
                  self.stopAnimation();
                }, 0);
                return;
              }

              var beforeStep = self.bot.dna[self.currentStep - 1];
              self.toggleTileState(beforeStep.i, beforeStep.j);

              var step = self.bot.dna[self.currentStep];
              if(step.i === -1 || step.j === -1) {
                return;
              }
              self.toggleTileState(step.i, step.j);
            }, 60);
          }
        }
      }

    });
  }

  window.addEventListener('load', onLoadWindow);
})();
