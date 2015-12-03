void Matrix3D_Copy(float a[4][4], float b[4][4])
{
	for (int r=0; r<4; r++)
	{
		for (int c=0; c<4; c++)
		{
			a[r][c] = b[r][c];
		}
	}
}

void Matrix3D_Multiply(float res[4][4], float a[4][4], float b[4][4])
{
	float tmp[4][4];
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			float sum = 0.0f;
			for (int i = 0; i < 4; i++)
			{
				sum += a[r][i] * b[i][c];
			}
			tmp[r][c] = sum;
		}
	}
	Matrix3D_Copy(res, tmp);
}

void Matrix3D_GetIdentity(float a[4][4])
{
	for (int r=0; r<4; r++)
	{
		for (int c=0; c<4; c++)
		{
			a[r][c] = (r==c) ? 1.0f : 0.0f;
		}
	}
}

void Matrix3D_Translate(float mtx[4][4], float inv[4][4], float dx, float dy, float dz)
{
	float tmp[4][4] = {};
	tmp[0][3] = dx;
	tmp[1][3] = dy;
	tmp[2][3] = dz;
	Matrix3D_Multiply(mtx,tmp,mtx);
	tmp[0][3] = -dz;
	tmp[1][3] = -dy;
	tmp[2][3] = -dx;
	Matrix3D_Multiply(inv,inv,tmp);
}

void Matrix3D_Scale(float mtx[4][4], float inv[4][4], float sx, float sy, float sz)
{
	float tmp[4][4] = {};
	tmp[0][0] = sx;
	tmp[1][1] = sy;
	tmp[2][2] = sz;
	Matrix3D_Multiply(mtx,tmp,mtx);
	tmp[0][0] = 1/sx;
	tmp[1][1] = 1/sy;
	tmp[2][2] = 1/sz;
	Matrix3D_Multiply(inv,inv,tmp);
}

void Matrix3D_RotateX(float mtx[4][4], float inv[4][4], float cs, float sn)
{
	float tmp[4][4] = {};
	tmp[1][1] =  cs; tmp[1][2] = -sn;
	tmp[2][1] =  sn; tmp[2][2] =  cs;
	Matrix3D_Multiply(mtx,tmp,mtx);
	tmp[1][1] =  cs; tmp[1][2] =  sn;
	tmp[2][1] = -sn; tmp[2][2] =  cs;
	Matrix3D_Multiply(inv,inv,tmp);
}

void Matrix3D_RotateX(float mtx[4][4], float inv[4][4], float radians)
{
	float cs, sn;
	cs = (float) cos(radians);
	sn = (float) sin(radians);
	Matrix3D_RotateX(mtx,inv,cs,sn);
}

void Matrix3D_RotateY(float mtx[4][4], float inv[4][4], float cs, float sn)
{
	float tmp[4][4] = {};
	tmp[0][0] =  cs; tmp[0][2] = -sn;
	tmp[2][0] =  sn; tmp[2][2] =  cs;
	Matrix3D_Multiply(mtx,tmp,mtx);
	tmp[0][0] =  cs; tmp[0][2] =  sn;
	tmp[2][0] = -sn; tmp[2][2] =  cs;
	Matrix3D_Multiply(inv,inv,tmp);
}

void Matrix3D_RotateY(float mtx[4][4], float inv[4][4], float radians)
{
	float cs, sn;
	cs = (float) cos(radians);
	sn = (float) sin(radians);
	Matrix3D_RotateY(mtx,inv,cs,sn);
}

void Matrix3D_RotateZ(float mtx[4][4], float inv[4][4], float cs, float sn)
{
	float tmp[4][4] = {};
	tmp[0][0] =  cs; tmp[0][1] = -sn;
	tmp[1][0] =  sn; tmp[1][1] =  cs;
	Matrix3D_Multiply(mtx,tmp,mtx);
	tmp[0][0] =  cs; tmp[0][1] =  sn;
	tmp[1][0] = -sn; tmp[1][1] =  cs;
	Matrix3D_Multiply(inv,inv,tmp);
}

void Matrix3D_RotateZ(float mtx[4][4], float inv[4][4], float radians)
{
	float cs, sn;
	cs = (float) cos(radians);
	sn = (float) sin(radians);
	Matrix3D_RotateZ(mtx,inv,cs,sn);
}

void Matrix3D_ReflectX(float mtx[4][4], float inv[4][4])
{
	float tmp[4][4] = {};
	tmp[0][0] = -1.0f;
	tmp[1][1] =  1.0f;
	tmp[2][2] =  1.0f;
	tmp[3][3] =  1.0f;
	Matrix3D_Multiply(mtx,tmp,mtx);
	Matrix3D_Multiply(inv,inv,tmp);
}

void Matrix3D_ReflectY(float mtx[4][4], float inv[4][4])
{
	float tmp[4][4] = {};
	tmp[0][0] =  1.0f;
	tmp[1][1] = -1.0f;
	tmp[2][2] =  1.0f;
	tmp[3][3] =  1.0f;
	Matrix3D_Multiply(mtx,tmp,mtx);
	Matrix3D_Multiply(inv,inv,tmp);
}

void Matrix3D_ReflectZ(float mtx[4][4], float inv[4][4])
{
	float tmp[4][4] = {};
	tmp[0][0] =  1.0f;
	tmp[1][1] =  1.0f;
	tmp[2][2] = -1.0f;
	tmp[3][3] =  1.0f;
	Matrix3D_Multiply(mtx,tmp,mtx);
	Matrix3D_Multiply(inv,inv,tmp);
}

void Matrix3D_MultiplyPoint(float out[3], float mtx[4][4], float in[3])
{
	float tmp[3] = {};
	for (int i=0; i < 3; i++)
	{
		tmp[i] = mtx[i][0]*in[0] + mtx[i][1]*in[1] + mtx[i][2]*in[2] + mtx[i][3];
	}
	out[0] = tmp[0];
	out[1] = tmp[1];
	out[2] = tmp[2];
}

void Matrix3D_MultiplyPoints(float *out[3], float mtx[4][4], float *in[3], int count)
{
	for (int i = 0; i < count; i++)
	{
		Matrix3D_MultiplyPoint(out[i], mtx, in[i]);
	}
}

void Matrix3D_CrossProduct(float res[3], float a[3], float b[3])
{
	float tmp[3] = {};
	tmp[0] = a[1]*b[2] - a[2]*b[1];
	tmp[1] = a[2]*b[0] - a[0]*b[2];
	tmp[2] = a[0]*b[1] - a[1]*b[0];

	res[0] = tmp[0];
	res[1] = tmp[1];
	res[2] = tmp[2];
}

int Matrix3D_View(float view[4][4], float view_inverse[4][4], float eye[3], float coi[3], float up[3], bool32 use_up)
{
	float vector[3];
	for(int i = 0; i < 3; i++)
	{
		vector[i] = coi[i] - eye[i];
	}

	float length_xz = (float) sqrt(vector[0]*vector[0] + vector[1]*vector[1]);
	float length = Vector3D_Length(vector);

	if (length_xz == 0 || length == 0) return 0;

	Matrix3D_GetIdentity(view);
	Matrix3D_GetIdentity(view_inverse);
	Matrix3D_Translate(view,view_inverse, -eye[0], -eye[1], -eye[2]);
	if (fabs(vector[1] < length_xz))
	{
		Matrix3D_RotateY(view,view_inverse, vector[1]/length_xz, -vector[0]/length_xz);
		Matrix3D_RotateX(view,view_inverse, length_xz/length, vector[2]/length);
	}
	else
	{
		Matrix3D_RotateX(view,view_inverse, vector[1]/length_xz, vector[2]/length_xz);
		Matrix3D_RotateZ(view,view_inverse, length_xz/length, -vector[0]/length);
	}
	if (use_up)
	{
		float up_tmp[3];
		float up_tmp_length;
		Matrix3D_MultiplyPoint(up_tmp,view,up);
		up_tmp_length = (float) sqrt(up_tmp[0]*up_tmp[0] + up_tmp[2]*up_tmp[2]);

		if (up_tmp_length == 0) return 0;

		Matrix3D_RotateY(view, view_inverse, up_tmp[2]/up_tmp_length, up_tmp[0]/up_tmp_length);
	}

	return 1;
}

int Matrix3D_View(float view[4][4], float view_inverse[4][4], float eye[3], float coi[3], float up[3])
{
	return Matrix3D_View(view, view_inverse, eye, coi, up, 1);
}

int Matrix3D_View(float view[4][4], float view_inverse[4][4], float eye[3], float coi[3])
{
	float up[3];
	up[0] = eye[0];
	up[1] = eye[1];
	up[2] = eye[2] + 1.0f;
	return Matrix3D_View(view, view_inverse, eye, coi, up, 0);
}