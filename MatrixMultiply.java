import java.util.Random;

public class MatrixMultiply {
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
		for (int i=0; i < nLines; i++) {
			for (int j=0; j < nColumns; j++) {
				A[i][j] = r.nextDouble();
				B[j][i] = r.nextDouble();
			}
		}
		long start = System.nanoTime();
		for (int i=0; i<nLines; i++) {
			for (int j=0; j<nLines; j++) {
				C[i][j] = 0;
				for (int k=0; k<nColumns; k++) {
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		long stop = System.nanoTime();
		double tdiff = (stop - start) * 1e-9;
		double nOps = 2*nLines*nColumns*nLines;
		double flops = nOps/tdiff;
		double speedup = flops/reference;
		System.out.printf ("%10s : (%d x %d) : %5.2f (s) : %d (ops) : %12.2f (flops) %12.2f (speedup)\n",
						   "Java", nLines, nColumns, tdiff, (int) nOps, flops, speedup);
	}
}
