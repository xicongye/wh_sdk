wire clk = top.dut.dut.tile_0.core.mem_access_unit.clock;
wire core0_io_dmem_req_ready = top.dut.dut.tile_0.core.mem_access_unit.io_dmem_2_req_ready;
wire core0_io_dmem_req_valid = top.dut.dut.tile_0.core.mem_access_unit.io_dmem_2_req_valid;
wire [4:0] core0_io_dmem_req_bits_cmd = top.dut.dut.tile_0.core.mem_access_unit.io_dmem_2_req_bits_cmd;
wire [31:0] core0_io_dmem_req_bits_addr = top.dut.dut.tile_0.core.mem_access_unit.io_dmem_2_req_bits_addr;
wire [`XLEN-1:0] core0_io_dmem_s1_data_data = top.dut.dut.tile_0.core.mem_access_unit.io_dmem_2_s1_data_data;
wire core0_io_dmem_s2_nack = top.dut.dut.tile_0.core.mem_access_unit.io_dmem_2_s2_nack;

reg [7:0] tmp0;
integer core0_printf_log;
initial begin
        core0_printf_log = $fopen("../sim_log/core0_printf.log");
end

always @(posedge clk)
begin
        if(core0_io_dmem_req_ready && 
            core0_io_dmem_req_valid && 
            (core0_io_dmem_req_bits_cmd == 5'b1) &&
            (core0_io_dmem_req_bits_addr == 32'h4100_0000))
        begin
            @(posedge clk);                       
            tmp0 = core0_io_dmem_s1_data_data[7:0];
            @(posedge clk);
            if(!core0_io_dmem_s2_nack) 
            begin
                $fwrite(core0_printf_log,"%c",tmp0);
                $fwrite(32'h80000002, "%c", tmp0);
            end 
         end                    
end