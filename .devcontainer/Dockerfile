FROM debian:12.4-slim

RUN apt-get update && apt-get install -y \
    sudo \ 
    build-essential \
    clang \
    clangd \
    git \
    locales \
    man-db \
    manpages-dev \
    meson \
    nano \
    python3-venv \
    vim \
    wget \
    zsh \
    && rm -rf /var/lib/apt/lists/*

RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && locale-gen

RUN sh -c "$(wget https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh -O -)" "" --unattended \
    && sed -i 's/ZSH_THEME="robbyrussell"/ZSH_THEME="lukerandall"/g' /root/.zshrc \
    && echo '\nexport VIRTUAL_ENV_DISABLE_PROMPT=1' >> /root/.zshrc

CMD ["zsh"]