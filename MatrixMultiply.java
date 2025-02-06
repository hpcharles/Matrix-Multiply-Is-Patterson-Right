import java.util.Random;

public class MatrixMultiply
{

	public static void multiplyKernel(double[][] A, double [][]B, double C[][], int line, int nLines, int nColumns)
	{
		for (int column=0; column< nLines; column++)
			{
				C[line][column] = 0;
				for (int k=0; k< nColumns; k++)
					{
						C[line][column] += A[line][k] * B[k][column];
					}
			}
	}

	public static void main(String[] args) {
		Random r = new Random();

		if (args.length < 3)
			{
				System.out.println ("Not enough arguments <nLines> <nCols> <referenceTime>");
				return;
			}
		int nLines    = Integer.parseInt(args[0]);
		int nColumns  = Integer.parseInt(args[1]);
		double reference = Float.parseFloat(args[2]);
		double[][] A = new double[nLines][nColumns];
		double[][] B = new double[nColumns][nLines];
		double[][] C = new double[nLines][nLines];
		for (int i=0; i < nLines; i++)
		{
			for (int column=0; column < nColumns; column++)
			{
				A[i][column] = r.nextDouble();
				B[column][i] = r.nextDouble();
			}
		}
		long start = System.nanoTime();
		for (int line=0; line<nLines; line++)
		{
			multiplyKernel (A, B, C, line, nLines, nColumns);
		}
		long stop = System.nanoTime();
		double tdiff = (stop - start) * 1e-9;
		double nOps = 2*nLines*nColumns*nLines/1000000;
		double flops = nOps/tdiff;
		double speedup = flops/reference;
		System.out.println("Version    ; size       ; time (s) ; #Gops ; Gflops; speedup");
		System.out.printf ("%10s ; %5dx%5d ; %5.2f ; %d  ; %12.2f ; %12.2f\n",
						   "Java", nLines, nColumns, tdiff, (int) nOps, flops, speedup);
		System.out.printf ("Dummy result : %f̣\n", C[0][0]);
	}
}
