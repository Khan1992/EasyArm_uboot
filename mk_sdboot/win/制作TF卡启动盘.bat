@echo off
echo. 
echo EasyARM-iMX28x ����SD����������
echo. 
echo ������SD���̷���
set /p diskpath=
set cmdpath=%~dp0
echo ע��:
echo �ļ��ᱻ��д�� %diskpath% ��
echo. 
rem ---------------------------------------------------------------------------------------------
rem %cmdpath%cfimager.exe -a -f %cmdpath%imx28_ivt_uboot.sb -d %diskpath%
%cmdpath%cfimager.exe -a -f %cmdpath%imx28_ivt_uboot.sb -e %cmdpath%rootfs.ext2.img -d %diskpath%
rem ---------------------------------------------------------------------------------------------
rem �ӵ�2048(0x800)��������ʼ���uImage,���ӵ�1048576(0x100000)�ֽڿ�ʼ���uImage
rem �ܹ�2048������,ÿ������512���ֽ�,������2048*512=1048576
rem %cmdpath%cfimager.exe -raw -offset 0x100000 -f %cmdpath%uImage -d %diskpath%
rem ---------------------------------------------------------------------------------------------
rem ��copy��uImage������FAT32������,����ֱ����д���FAT32������Ϣ���ƻ�.
rem ����uboot֧�ֶ�fat32�ļ�ϵͳ�Ķ�д,���Կ���ֱ��ʹ��uboot��fatload�����
rem uImage���ص��ڴ��в�����. ����Ϊ:"fatload mmc 0:1 $(loadaddr) uImage;bootm"
copy %cmdpath%uImage %diskpath%: /y
rem ---------------------------------------------------------------------------------------------
rem ��ȫ0�ļ����uboot���������������
rem uboot�Ļ�������Ĭ�ϴ���ڴӵ�1024(0x400)�ֽڴ���ʼ��127Kb�ռ���
%cmdpath%cfimager.exe -raw -offset 0x400 -f %cmdpath%zero.raw -d %diskpath%
rem ---------------------------------------------------------------------------------------------
echo ��д��ϣ������˳�
echo.
pause>nul