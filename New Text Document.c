(async () => {
  const sleep = ms => new Promise(r => setTimeout(r, ms));
  let removed = 0;

  const strategy = 'middle-bottom'; // choose: 'middle-top', 'middle-bottom', 'bottom-top', 'alphabetical', 'reverse-alphabetical'

  while (true) {
    // 1️⃣ Load all currently visible videos
    let cards = Array.from(document.querySelectorAll('ytd-playlist-video-renderer'));
    if (cards.length === 0) {
      console.log("No videos found. Make sure you're on the Liked videos playlist.");
      break;
    }

    // 2️⃣ Sort based on strategy
    switch(strategy) {
      case 'middle-top':
        const midTop = Math.floor(cards.length / 2);
        cards = cards.slice(0, midTop + 1).reverse(); // middle → top
        break;
      case 'middle-bottom':
        const midBottom = Math.floor(cards.length / 2);
        cards = cards.slice(midBottom); // middle → bottom
        break;
      case 'bottom-top':
        cards = cards.reverse(); // bottom → top
        break;
      case 'alphabetical':
        cards = cards
          .map(c => ({ c, name: (c.querySelector('#video-title')?.textContent||'').trim().toLowerCase() }))
          .sort((a,b)=>a.name.localeCompare(b.name))
          .map(o=>o.c);
        break;
      case 'reverse-alphabetical':
        cards = cards
          .map(c => ({ c, name: (c.querySelector('#video-title')?.textContent||'').trim().toLowerCase() }))
          .sort((a,b)=>b.name.localeCompare(a.name))
          .map(o=>o.c);
        break;
    }

    let removedThisRound = 0;

    // 3️⃣ Remove videos
    for (const card of cards) {
      try {
        card.scrollIntoView({ block:'center', behavior:'auto' });
        await sleep(300);

        const menuBtn = card.querySelector(
          'ytd-menu-renderer yt-icon-button, ytd-menu-renderer #button, #menu tp-yt-paper-icon-button, button[aria-label*="Action menu"], button[aria-label*="More actions"], #more'
        );
        if (!menuBtn) continue;

        menuBtn.click();
        await sleep(400);

        const menuItems = Array.from(document.querySelectorAll(
          'ytd-menu-service-item-renderer, tp-yt-paper-item, tp-yt-paper-listbox ytd-menu-service-item-renderer, yt-formatted-string'
        ));

        const target = menuItems.find(el => /remove.*(like|liked)|unlike|remove from liked|remove from liked videos|remove from playlist/i.test((el.innerText||el.textContent||'').toLowerCase()));

        if (target) {
          target.click();
          removed++;
          removedThisRound++;
          const title = (card.querySelector('#video-title')?.textContent||card.textContent||'').trim().slice(0,80);
          console.log(`(${removed}) Removed: ${title}`);
          await sleep(700);
        } else {
          document.dispatchEvent(new KeyboardEvent('keydown',{key:'Escape',keyCode:27,which:27}));
          await sleep(200);
        }
      } catch(err) {
        console.error('Error removing video', err);
        await sleep(500);
      }
    }

    // 4️⃣ Scroll to load more if nothing was removed
    if (removedThisRound === 0) {
      window.scrollBy(0, 2200);
      await sleep(1200);

      // Check if new cards loaded
      const newCount = document.querySelectorAll('ytd-playlist-video-renderer').length;
      if (newCount <= cards.length) {
        console.log("No more videos to remove. Finished.");
        break;
      }
    }
  }

  console.log('All done. Total removed:', removed);
})();
