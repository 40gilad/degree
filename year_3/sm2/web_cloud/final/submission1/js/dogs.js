const addDogBtn = document.querySelector('[data-bs-target="#addDogModal"]');
		const addDogModal = document.querySelector('#addDogModal');
		const closeModalBtn = addDogModal.querySelector('.modal-footer button');

		function openModal() {
			addDogModal.classList.add('show');
			addDogModal.style.display = 'block';
		}

		function closeModal() {
			addDogModal.classList.remove('show');
			addDogModal.style.display = 'none';
		}

		addDogBtn.addEventListener('click', openModal);

		closeModalBtn.addEventListener('click', closeModal);