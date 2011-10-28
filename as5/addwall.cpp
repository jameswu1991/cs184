
MatrixXf front (8, 3);
front << -1.5f, -1.0f, 1.5f,
	1.5f, -1.0f, 1.5f,
	1.5f, 1.0f, 1.5f,
	-1.5f, 1.0f, 1.5f,
	-1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, 1.0f;
window.addQuad(front.transpose());

MatrixXf right (8, 3);
right << 1.5f, -1.0f, -1.5f,
	1.5f, 1.0f, -1.5f,
	1.5f, 1.0f, 1.5f,
	1.5f, -1.0f, 1.5f,
	1.0f, 0.0f, -1.0f,
	1.0f, 0.0f, -1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f;
window.addQuad(right.transpose());

MatrixXf back (8, 3);
back << -1.5f, -1.0f, -1.5f,
	-1.5f, 1.0f, -1.5f,
	1.5f, 1.0f, -1.5f,
	1.5f, -1.0f, -1.5f,
	-1.0f, 0.0f, -1.0f,
	-1.0f, 0.0f, -1.0f,
	1.0f, 0.0f, -1.0f,
	1.0f, 0.0f, -1.0f;
window.addQuad(back.transpose());

MatrixXf left (8, 3);
left << -1.5f, -1.0f, -1.5f,
	-1.5f, -1.0f, 1.5f,
	-1.5f, 1.0f, 1.5f,
	-1.5f, 1.0f, -1.5f,
	-1.0f, 0.0f, -1.0f,
	-1.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, -1.0f;
window.addQuad(left.transpose());
