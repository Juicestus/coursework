const menuWrap = document.querySelector('.menu-wrap');
  const btn = document.querySelector('.hamburger-btn');
  const menu = document.querySelector('.menu');

  function openMenu() {
    menuWrap.classList.add('open');
    btn.setAttribute('aria-expanded', 'true');
    addBackdrop();
  }
  function closeMenu() {
    menuWrap.classList.remove('open');
    btn.setAttribute('aria-expanded', 'false');
    removeBackdrop();
  }
  function toggleMenu() {
    menuWrap.classList.toggle('open');
    btn.setAttribute('aria-expanded', String(menuWrap.classList.contains('open')));
    if (menuWrap.classList.contains('open')) addBackdrop(); else removeBackdrop();
  }

  // Toggle on button tap (mobile) — hover still works on desktop
  btn.addEventListener('click', (e) => {
    e.stopPropagation();
    toggleMenu();
  });

  // Close when a menu link is tapped/clicked
  menu.addEventListener('click', (e) => {
    if (e.target.closest('a')) closeMenu();
  });

  // Close on any tap/click outside (pointerdown works best on mobile)
  function onOutsidePointer(e) {
    if (!menuWrap.contains(e.target)) closeMenu();
  }
  document.addEventListener('pointerdown', onOutsidePointer);

  // Also close on Escape (hardware keyboards)
  document.addEventListener('keydown', (e) => {
    if (e.key === 'Escape') closeMenu();
  });

  // Optional: close on orientation change / resize
  window.addEventListener('orientationchange', closeMenu);
  window.addEventListener('resize', closeMenu);

  // -------- Backdrop helpers --------
  function addBackdrop() {
    if (document.querySelector('.menu-backdrop')) return;
    const bd = document.createElement('div');
    bd.className = 'menu-backdrop';
    bd.addEventListener('pointerdown', closeMenu, { once: true });
    document.body.appendChild(bd);
  }
  function removeBackdrop() {
    const bd = document.querySelector('.menu-backdrop');
    if (bd) bd.remove();
  }
