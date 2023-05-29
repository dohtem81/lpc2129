Baseline project to use ENC28J60 ethernet module. 

Comunication between uP and ENC is over spi. Spi driver is pretty simple. To initialize **spi_initialize**, and then you use **spi_read** and **spi_write** functions.

Treat ENC28J60.c and header file as a driver. To initialize module call **enc_initialize** function. To adjust MAC and IP addresses see addresses section in ENC header file.

# lpc2129 # ENC28J60
