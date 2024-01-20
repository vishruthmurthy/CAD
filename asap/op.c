module Transmitter(bus t);
	always_ff @(posedge t.clk)
	begin
		if(t.vaild && !t.ready)
		begin
			
		end
	end
endmodule




/*
module Transmitter(bus b);
	always_ff@(posedge b.clk)
	begin
		b.write(b.data_in);
	end
endmodule*/interface bus(input clk);
	logic [7:0] in;
	logic [7:0] out;
	logic [7:0] bus;
	bit valid;
	bit ready;

  modport tx(input in, valid, ready, output bus);
  modport rx(input bus, valid, ready, output out);
         
endinterface

module top;
  
   reg valid,ready;
   bit clk = 1'b0;
   reg [7:0] data_in;
   wire data_out;

   parallel intf(clk,valid,ready,data_in);


   always #5 clk = ~clk;

   initial 
     begin
        valid = 1'b1;
        ready = 1'b0;
        data_in = 8'b11011011;
        #20 valid = 1'b0;
            ready = 1'b1;
     end

endmodule       

module decoder_2bit(en,a,b,y);
  input en,a,b;
  output reg [3:0] y;  
  
  assign en = fsm.out;
  
  always@(en)begin
          case({a,b})
                 2'b00:y = 4'b0001;
                 2'b01:y = 4'b0010;
                 2'b10:y = 4'b0100;
                 2'b11:y = 4'b1000;
          endcase
   end
endmodule
                 
           module top;
  
   reg valid,ready;
   bit clk = 1'b0;
   reg [7:0] data_in;
   wire data_out;

   parallel intf(clk,valid,ready,data_in);


   always #5 clk = ~clk;

   initial 
     begin
        valid = 1'b1;
        ready = 1'b0;
        data_in = 8'b11011011;
        #20 valid = 1'b0;
            ready = 1'b1;
     end

endmodule       


