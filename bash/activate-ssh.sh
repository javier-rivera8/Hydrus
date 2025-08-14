#!/bin/bash
echo "=== Verificando OpenSSH Server ==="
if dpkg -l | grep -q openssh-server; then
  echo "OpenSSH Server ya está instalado."
else
  echo "OpenSSH Server no está instalado. Instalando..."
  sudo apt update
  sudo apt install -y openssh-server
fi

echo "=== Verificando estado del servicio SSH ==="
if systemctl is-active --quiet ssh; then
  echo "El servicio SSH ya está activo."
else
  echo "El servicio SSH no está activo. Iniciando servicio..."
  sudo systemctl start ssh
fi

echo "=== Habilitando servicio SSH para inicio automático ==="
sudo systemctl enable ssh

echo "=== Estado final del servicio SSH ==="
sudo systemctl status ssh --no-pager

echo "=== Comprobando puerto 22 ==="
sudo ss -tnlp | grep :22 || echo "El puerto 22 no está en escucha."

echo "=== Prueba de conexión SSH local ==="
ssh -o ConnectTimeout=5 localhost && echo "Conexión SSH local exitosa" || echo "No se pudo conectar por SSH localmente."

echo "=== Script finalizado ==="
