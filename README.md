# Scalar-Pipeline-Simulator
This program simulates as instruction pipeline for a processor. It includes the following stages

### Stages
1. [**Fetch**](#fetch-stage)
2. [**Decode**](#decode-stage)
3. [**Execute**](#execute-stage)
4. [**Memory**](#memory-stage)
5. [**WriteBack**](#writeback-stage)

The pipeline is designed to handle various types of instructions and their execution involving *hazards*.
### Hazards
> - [**Data Hazard**](#data-hazard) (RAW - Read After Write) 
> - [**Control Hazard**](#control-hazard)

### Input Files:
1. [**main.cpp**](/main.cpp): Contains the Logic and the Execution of the Pipeline Simulation
2. [**ICache.txt**](/input/ICache.txt): Input file containing Instructions to be fetched.
3. [**DCache.txt**](/input/DCache.txt): Input file containing data for Memory Operations.
4. [**RF.txt**](/input/RF.txt): Input file containing the Register Values.

The program will read instructions, data and register values and simulate the instruction pipeline.

## Stage Descriptions

### Fetch Stage
> - The Fetch Stage is responsible for retrieving the next instruction to be executed from memory.
> - The instruction is fetched from memory and loaded into a temporary register for further processing.
> - During this stage, the Program Counter(PC) is incremented or updated to point to the address of the next instruction.

### Decode Stage
> - In Decode Stage, the fetched instruction is decoded to determine its type and required operations.
> - The instruction's operation code(opcode) is extracted to identify the type of instruction as
>   - Arithmetic
>   - Logical
>   - Memory Access
>   - Control Flow
> - Depending on the instruction type, the decode stage sets up the appropriate control signals and prepares operand values for the execution stage.
> - For instructions involving registers or memory addresses, the decode stage identifies the specific registers or memory locations involved in the operation.


### Execute Stage
> - The Execution Stage is where the actual computation or operation specified by the instruction takes place.
> - Control signals generated in the decode stage guide the ALU to perform various operations on the operand values obtained from registers or immediate values.
> - For instructions like branches or jumps, the execute stage evaluates conditions and updates the Program Counter accordingly to alter the program flow.


### Memory Stage
> - In Memory Stage, instructions that involve memory access are executed.
> - This stage includes loading data from memory or storing data to memory.

### Writeback Stage
> - The Writeback Stage finalizes the instruction execution by updating the register file with the result.

## Handling Hazards

### Data Hazard
> - Data Hazards also known as **RAW** (Read After Write) Hazards occur when an instruction depends on the result of a previous instruction whose result has not yet been written back to the register file
> - This situation can lead to incorrect results if not handled properly as we will not be using the updated values.
> - The data hazards are handled by introducing `Stalls`.
> - Stalls are essentially `no-operation` instructions that do not perform any meaningful operation but serve to delay the pipeline execution.
> - This is typically achieved by monitoring dependencies between instructions
>   - For example: Checking if the operands of an instruction are being modified by a previous instruction that has not yet completed its writeback stage.

### Control Hazard
> - Control hazards occur when the next instruction to be executed depends on the result of a previous instruction whose outcome is not yet known.
> - This commonly occurs with `branch instructions` where the execution path depends on a condition that is determined during execution state in the pipeline.
> - The control hazards are handled by introducing stalls to prevent incorrect execution due to branches.


## Compilation
> - Compile the program using a C++ compiler using the following commands
```bash
   g++ main.cpp
   # run the executable accordingly (below is given for windows)
   ./a.exe
```

## Output Files
> - [**Output.txt**](/output/Output.txt): Contains simulation results including the number of instructions executed, instruction classes, cycles per instruction, and stall information.
> - [**DCache.txt**](/output/DCache.txt): Contains updated data after memory operations.

> [!NOTE]
> [Output.txt](/output/Output.txt) and [DCache.txt](/output/DCache.txt) files should be present in Output folder beforehand.